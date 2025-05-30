#include "Framework.h"

Panel::Panel(wstring imagePath, Vector2 pos)
{
	quad = new Quad(imagePath, Vector2(0, 0), Vector2(1.0f, 1.0f));
	SetLocalPosition(pos);
	quad->SetParent(this);
	UpdateWorld();
	quad->UpdateWorld();
}

Panel::~Panel()
{
	delete quad;
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
}

void Panel::Render()
{
	quad->Render();
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
		//button->SetOnClick(bind(&함수이름, this));
		button->SetOnClick(bind(&AllyManager::Spawn, AllyManager::Get(), ALLY_TYPE::Boxer));
		this->AddButton(button);
	}
}
