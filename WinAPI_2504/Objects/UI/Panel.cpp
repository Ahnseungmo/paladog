#include "Framework.h"

Panel::Panel(Vector2 pos)
{
	SetLocalPosition(pos);

	panelTexture = new Quad(L"Resources/Textures/UI/PlayerPanel.png");
	panelTexture->SetParent(this);

	spawnBar = new SpawnBar();
	spawnBar->SetParent(this);

	UpdateWorld();
	panelTexture->UpdateWorld();
	spawnBar->UpdateWorld();
}

Panel::~Panel()
{
	delete panelTexture;
	delete spawnBar;
}

void Panel::AddButton(Button* button)
{
	buttons.push_back(button);
	button->UpdateWorld();
	button->SetParent(this);
}

void Panel::Update()
{
	UpdateWorld();
	for (auto button : buttons)
		button->Update();
	spawnBar->Update();
}

void Panel::Render()
{
	spawnBar->Render();
	panelTexture->Render();
	for (auto button : buttons)
		button->Render();
}

void Panel::CreateButtons()
{
	int buttonCount = 10;
	float buttonWidth = 120.0f;
	float buttonSpacing = 5.0f;
	float startX = -((buttonCount - 1) * (buttonWidth + buttonSpacing)) / 2.0f;

	for (int i = 0; i < buttonCount; ++i)
	{
		float x = this->GetLocalPosition().x + startX + i * (buttonWidth + buttonSpacing);
		float y = this->GetLocalPosition().y + 15;
		Button* button = new Button(L"Resources/Textures/UI/TestButton.png", Vector2(50, 50), Vector2(x, y));
		//button->SetOnClick(bind(&AllyManager::Spawn, AllyManager::Get(), ALLY_TYPE::Boxer));
		//button->SetIntParam(bind(&Panel::SpawnCharacter, this, i));
		button->SetOnClick([this, i]() { SpawnCharacter(i); });
		this->AddButton(button);
	}
}

void Panel::SpawnCharacter(int type)
{
	switch (type)
	{
	case 0:
		if (spawnBar->GetCurSpawn() > 10)
		{
			spawnBar->SetCurSpawn(spawnBar->GetCurSpawn() -10);
			AllyManager::Get()->Spawn(ALLY_TYPE::Knight);
		}
		break;
	case 1:
		if (spawnBar->GetCurSpawn() > 20)
		{
			spawnBar->SetCurSpawn(spawnBar->GetCurSpawn() -20);
			AllyManager::Get()->Spawn(ALLY_TYPE::Archer);
		}
		break;
	case 2:
		if (spawnBar->GetCurSpawn() > 30)
		{
			spawnBar->SetCurSpawn(spawnBar->GetCurSpawn() -30);
			AllyManager::Get()->Spawn(ALLY_TYPE::Boxer);
		}
		break;
	case 3:
		if (spawnBar->GetCurSpawn() > 40)
		{
			spawnBar->SetCurSpawn(spawnBar->GetCurSpawn() -40);
			AllyManager::Get()->Spawn(ALLY_TYPE::Lancer);
		}
		break;
	case 4:
		if (spawnBar->GetCurSpawn() > 50)
		{
			spawnBar->SetCurSpawn(spawnBar->GetCurSpawn() - 50);
			AllyManager::Get()->Spawn(ALLY_TYPE::Tanker);
		}
		break;
	}
}