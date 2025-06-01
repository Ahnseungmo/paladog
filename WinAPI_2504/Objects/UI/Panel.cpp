#include "Framework.h"

Panel::Panel(Vector2 pos)
{
	SetLocalPosition(pos);

	CreateButtons();
	CreateCoolTimeButtons();

	panelTexture = new Quad(L"Resources/Textures/UI/PlayerPanel.png");
	panelTexture->SetParent(this);

	spawnBar = new GaugeBar(5.0f, Vector2(370, 33), Vector2(273, 258), 
		L"Resources/Textures/UI/curSpawnBar.png",
		L"Resources/Textures/UI/maxBar.png");

	manaBar = new GaugeBar(5.0f, Vector2(370, 33), Vector2(1010, 258),
		L"Resources/Textures/UI/curManaBar.png",
		L"Resources/Textures/UI/maxBar.png"); 

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
	for (int i = 0; i < 5; i++)
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
}

void Panel::Render()
{
	spawnBar->Render();
	manaBar->Render();
	panelTexture->Render();
	for (auto button : buttons)
		button->Render();
	for (auto button : coolTimeButtons)
		button->Render();
}

void Panel::CreateButtons()
{
	int buttonCount = 5;
	float buttonWidth = 120.0f;
	float buttonSpacing = 5.0f;
	float startX = -((buttonCount - 1) * (buttonWidth + buttonSpacing)) / 2.0f;

	wstring buttonTextures[] = {
		L"Resources/Textures/UI/KnightButton.png",
		L"Resources/Textures/UI/ArcherButton.png",
		L"Resources/Textures/UI/LancerButton.png",
		L"Resources/Textures/UI/BoxerButton.png",
		L"Resources/Textures/UI/TankerButton.png"
	};

	for (int i = 0; i < buttonCount; ++i)
	{
		float x = this->GetLocalPosition().x + startX + i * (buttonWidth + buttonSpacing);
		float y = this->GetLocalPosition().y + 15;
		Button* button = new Button(buttonTextures[i], Vector2(100, 100), Vector2(x, y));
		//button->SetOnClick(bind(&AllyManager::Spawn, AllyManager::Get(), ALLY_TYPE::Boxer));
		button->SetOnClick([this, i]() { SpawnCharacter(i); });
		this->AddButton(button);
	}

	Button* meatButton = new Button(L"Resources/Textures/UI/MeatButton.png", Vector2(100, 100), Vector2(753, 61));
	Button* healButton = new Button(L"Resources/Textures/UI/HealButton.png", Vector2(100, 100), Vector2(953, 61));
	Button* punchButton = new Button(L"Resources/Textures/UI/PunchButton.png", Vector2(100, 100), Vector2(1153, 61));

	meatButton->SetOnClick(bind(&Panel::MeatSkill, this));
	punchButton->SetOnClick([this]() { if (paladog) paladog->PunchSkill(); });

	this->AddButton(meatButton);
	this->AddButton(healButton);
	this->AddButton(punchButton);
}

void Panel::CreateCoolTimeButtons()
{
	int buttonCount = 5;
	float buttonWidth = 120.0f;
	float buttonSpacing = 5.0f;
	float startX = -((buttonCount - 1) * (buttonWidth + buttonSpacing)) / 2.0f;

	wstring buttonCoolTimeTextures[] = {
		L"Resources/Textures/UI/KnightCoolTimeButton.png",
		L"Resources/Textures/UI/ArcherCoolTimeButton.png",
		L"Resources/Textures/UI/LancerCoolTimeButton.png",
		L"Resources/Textures/UI/BoxerCoolTimeButton.png",
		L"Resources/Textures/UI/TankerCoolTimeButton.png"
	};

	for (int i = 0; i < buttonCount; ++i)
	{
		float x = this->GetLocalPosition().x + startX + i * (buttonWidth + buttonSpacing);
		float y = this->GetLocalPosition().y + 15;
		Button* button = new Button(buttonCoolTimeTextures[i], Vector2(100, 100), Vector2(x, y));
		//button->SetOnClick(bind(&AllyManager::Spawn, AllyManager::Get(), ALLY_TYPE::Boxer));
		//button->SetOnClick([this, i]() { SpawnCharacter(i); });
		button->SetActive(false);
		this->AddCoolTimeButton(button);
	}
}

void Panel::SpawnCharacter(int type)
{
	switch (type)
	{
	case 0:
		if (coolTimeCounts[0] >= maxCoolTime[0] && spawnBar->GetCurGauge() > 10)
		{
			spawnBar->SetCurGauge(spawnBar->GetCurGauge() -10);
			AllyManager::Get()->Spawn(ALLY_TYPE::Bomber);
			coolTimeCounts[0] = 0;
			coolTimeButtons[0]->SetActive(true);
		}
		break;
	case 1:
		if (coolTimeCounts[1] >= maxCoolTime[1] && spawnBar->GetCurGauge() > 20)
		{
			spawnBar->SetCurGauge(spawnBar->GetCurGauge() -20);
			AllyManager::Get()->Spawn(ALLY_TYPE::Archer);
			coolTimeCounts[1] = 0;
			coolTimeButtons[1]->SetActive(true);
		}
		break;
	case 2:
		if (coolTimeCounts[2] >= maxCoolTime[2] && spawnBar->GetCurGauge() > 30)
		{
			spawnBar->SetCurGauge(spawnBar->GetCurGauge() - 30);
			AllyManager::Get()->Spawn(ALLY_TYPE::Lancer);
			coolTimeCounts[2] = 0;
			coolTimeButtons[2]->SetActive(true);
		}
		break;
	case 3:
		if (coolTimeCounts[3] >= maxCoolTime[3] && spawnBar->GetCurGauge() > 40)
		{
			spawnBar->SetCurGauge(spawnBar->GetCurGauge() - 40);
			AllyManager::Get()->Spawn(ALLY_TYPE::Boxer);
			coolTimeCounts[3] = 0;
			coolTimeButtons[3]->SetActive(true);
		}
		break;
	case 4:
		if (coolTimeCounts[4] >= maxCoolTime[4] && spawnBar->GetCurGauge() > 50)
		{
			spawnBar->SetCurGauge(spawnBar->GetCurGauge() - 50);
			AllyManager::Get()->Spawn(ALLY_TYPE::Tanker);
			coolTimeCounts[4] = 0;
			coolTimeButtons[4]->SetActive(true);
		}
		break;
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
