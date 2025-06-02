#include "Framework.h"

Panel::Panel(Vector2 pos)
{
	SetLocalPosition(pos);

	panelTexture = new Quad(L"Resources/Textures/UI/PlayerPanel.png");
	panelTexture->SetParent(this);

	spawnBar = new GaugeBar(5.0f, Vector2(370, 33), Vector2(273, 258),
		L"Resources/Textures/UI/curSpawnBar.png",
		L"Resources/Textures/UI/maxBar.png");

	manaBar = new GaugeBar(5.0f, Vector2(370, 33), Vector2(1010, 258),
		L"Resources/Textures/UI/curManaBar.png",
		L"Resources/Textures/UI/maxBar.png");

	for (int i = 0; i < deck.size(); i++)
	{
		ALLY_TYPE allyType = static_cast<ALLY_TYPE>(deck[i]);
		const AllyData& data = DataManager::Get()->GetAlly(static_cast<int>(allyType));
		maxCoolTime[i] = data.cost / 10.0f;
		coolTimeCounts[i] = data.cost / 10.0f;
	}

	hpBar = new HealthBar(400, 30);
	hpBar->SetBarColor(0.3f, 0.3f, 1);

	UpdateWorld();
	panelTexture->UpdateWorld();
	spawnBar->UpdateWorld();
	manaBar->UpdateWorld();
}

Panel::~Panel()
{
	delete panelTexture;
	delete spawnBar;
	delete manaBar;

	delete hpBar;
}

void Panel::Start() {
	for (auto& button : buttons)
		delete button;
	buttons.clear();
	CreateButtons();
	CreateCoolTimeButtons();
}


void Panel::AddButton(Button* button)
{
	buttons.push_back(button);
	button->UpdateWorld();
	button->SetParent(this);
}

void Panel::AddCoolTimeButton(Button* button)
{
	coolTimeButtons.push_back(button);
	button->UpdateWorld();
	button->SetParent(this);
}

void Panel::Update()
{
	for (int i = 0; i < deck.size(); i++)
	{
		if (coolTimeCounts[i] < maxCoolTime[i])
			coolTimeCounts[i] += DELTA;
		coolTimeButtons[i]->SetActive(coolTimeCounts[i] < maxCoolTime[i]);
		coolTimeButtons[i]->GetQuad()->SetActive(coolTimeCounts[i] < maxCoolTime[i]);
	}

	UpdateWorld();
	for (auto button : buttons)
		button->Update();
	for (auto button : coolTimeButtons)
		button->Update();
	spawnBar->Update();
	manaBar->Update();
	hpBar->Update(CENTER, 700, paladog->GetHP(), paladog->GetStat().maxHp);
}

void Panel::Render()
{
	spawnBar->Render();
	manaBar->Render();
	hpBar->Render();
	panelTexture->Render();
	for (auto button : buttons)
		button->Render();
	for (auto button : coolTimeButtons)
		button->Render();
}

void Panel::CreateButtons()
{
	int buttonCount = deck.size();
	float buttonWidth = 120.0f;
	float buttonSpacing = 5.0f;
	float startX = -((buttonCount - 1) * (buttonWidth + buttonSpacing)) / 2.0f;

	unordered_map<int, wstring> unitImages = {
	{1001, L"Resources/Textures/Paladog/Unit/Knight.png"},
	{1002, L"Resources/Textures/Paladog/Unit/Archer.png"},
	{1003, L"Resources/Textures/Paladog/Unit/Boxer.png"},
	{1004, L"Resources/Textures/Paladog/Unit/Lancer.png"},
	{1005, L"Resources/Textures/Paladog/Unit/Tanker.png"},
	{1006, L"Resources/Textures/Paladog/Unit/Elite.png"},
	{1007, L"Resources/Textures/Paladog/Unit/Bomber.png"}
	};
	//	auto it = deck.begin();
	for (int i = 0; i < buttonCount; ++i)
	{
		float x = startX + i * (buttonWidth + buttonSpacing);
		float y = 15;

		Button* button = new Button(unitImages[deck[i]], Vector2(100, 100), Vector2(x, y));
		button->SetOnClick([this, i]() { SpawnCharacter(i); });
		this->AddButton(button);
		//	it++;
	}
	Button* meatButton = new Button(L"Resources/Textures/UI/MeatButton.png", Vector2(100, 100), Vector2(100, -100));
	Button* healButton = new Button(L"Resources/Textures/UI/HealButton.png", Vector2(100, 100), Vector2(300, -100));
	Button* punchButton = new Button(L"Resources/Textures/UI/PunchButton.png", Vector2(100, 100), Vector2(500, -100));

	meatButton->SetOnClick(bind(&Panel::MeatSkill, this));
	healButton->SetOnClick(bind(&Panel::HealSkill, this));
	punchButton->SetOnClick([this]() { if (paladog) paladog->PunchSkill(); });

	this->AddButton(meatButton);
	this->AddButton(healButton);
	this->AddButton(punchButton);
}

void Panel::CreateCoolTimeButtons()
{
	int buttonCount = deck.size();
	float buttonWidth = 120.0f;
	float buttonSpacing = 5.0f;
	float startX = -((buttonCount - 1) * (buttonWidth + buttonSpacing)) / 2.0f;

	unordered_map<int, wstring> unitImages = {
	{1001, L"Resources/Textures/UI/KnightCoolTimeButton.png"},
	{1002, L"Resources/Textures/UI/ArcherCoolTimeButton.png"},
	{1003, L"Resources/Textures/UI/BoxerCoolTimeButton.png"},
	{1004, L"Resources/Textures/UI/LancerCoolTimeButton.png"},
	{1005, L"Resources/Textures/UI/TankerCoolTimeButton.png"},
	{1006, L"Resources/Textures/UI/EliteCoolTimeButton.png"},
	{1007, L"Resources/Textures/UI/BomberCoolTimeButton.png"}
	};

	for (int i = 0; i < buttonCount; ++i)
	{
		float x = startX + i * (buttonWidth + buttonSpacing);
		float y = 15;
		Button* button = new Button(unitImages[deck[i]], Vector2(100, 100), Vector2(x, y));
		button->SetActive(false);
		this->AddCoolTimeButton(button);
	}
}

void Panel::SpawnCharacter(int typeIndex)
{
	ALLY_TYPE allyType = static_cast<ALLY_TYPE>(deck[typeIndex]);

	const AllyData& ally = DataManager::Get()->GetAlly(static_cast<int>(allyType));

	if (coolTimeCounts[typeIndex] >= maxCoolTime[typeIndex] &&
		spawnBar->GetCurGauge() > ally.cost)
	{
		spawnBar->SetCurGauge(spawnBar->GetCurGauge() - ally.cost);

		AllyManager::Get()->Spawn(allyType);

		coolTimeCounts[typeIndex] = 0;
		coolTimeButtons[typeIndex]->SetActive(true);
	}
}

void Panel::MeatSkill()
{
	if (manaBar->GetCurGauge() > 10 && spawnBar->GetCurGauge() <= spawnBar->GetMaxGauge())
	{
		manaBar->SetCurGauge(manaBar->GetCurGauge() - 10);
		spawnBar->SetCurGauge(spawnBar->GetCurGauge() + 50);
		if (spawnBar->GetCurGauge() > spawnBar->GetMaxGauge())
			spawnBar->SetCurGauge(spawnBar->GetMaxGauge());
	}
}

void Panel::HealSkill()
{
	if (manaBar->GetCurGauge() < HEAL_COST)
		return;

	manaBar->SetCurGauge(manaBar->GetCurGauge() - HEAL_COST);

	RectCollider* auraCollider = paladog->GetAuraCollider();
	float auraX = auraCollider->GetGlobalPosition().x;
	float auraHalfWidth = auraCollider->Size().x * 0.5f;
	float left = auraX - auraHalfWidth;
	float right = auraX + auraHalfWidth;

	vector<Character*>* allies = AllyManager::Get()->GetAllUnits();
	for (auto ally : *allies)
	{
		if (!ally->IsActive()) continue;

		float allyX = ally->GetGlobalPosition().x;
		if (allyX >= left && allyX <= right)
		{
			float newHP = ally->GetHP() + HEAL_AMOUNT;
			if (newHP > ally->GetMaxHP())
				newHP = ally->GetMaxHP();
			ally->SetHP(newHP);
		}
	}
}
















