#include "Framework.h"
#include "UpgradeScene.h"

UpgradeScene::UpgradeScene()
{
	backGround = new Quad(L"Resources/Textures/Paladog/LobbyBackGround.png", Vector2(0, 0), Vector2(1.0f, 1.0f));
	backGround->SetLocalPosition(CENTER);
	backGround->UpdateWorld();

	float buttonY[4] = {};
	buttonY[0] = CENTER_Y;
	for (int i = 1; i < 4; i++) {
		buttonY[i] = buttonY[i - 1] - BUTTON_PADDING;
	}

	buttons.insert(make_pair("Lobby", new Button(L"Resources/Textures/Paladog/Lobby/btn_ui_battle_up.png", Vector2(100, 50), Vector2(CENTER_X + 200, SCREEN_HEIGHT - 200))));
	buttons["Lobby"]->SetOnClick(bind(&UpgradeScene::Lobby, this));
	buttons["Lobby"]->Update();

}

UpgradeScene::~UpgradeScene()
{
	delete backGround;
	for (pair<string, Button*> button : buttons)
	{
		delete button.second;
	}
	buttons.clear();
}

void UpgradeScene::Update()
{
	for (auto& button : buttons) {
		button.second->Update();
	}
}

void UpgradeScene::Render()
{
	backGround->Render();
	for (auto& button : buttons) {
		button.second->Render();
	}
}

void UpgradeScene::GUIRender()
{
}

void UpgradeScene::Lobby()
{
	SCENE->ChangeScene("Lobby");

}
