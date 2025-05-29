#include "Framework.h"
#include "LobbyScene.h"

LobbyScene::LobbyScene()
{
	backGround = new Quad(L"Resources/Textures/Paladog/LobbyBackGround.png", Vector2(0, 0), Vector2(1.0f, 1.0f));
	backGround->SetLocalPosition(CENTER);
	backGround->UpdateWorld();
	
	buttons.insert(make_pair("Start", new Button(L"Resources/Textures/Paladog/LobbyButton.png", Vector2(100, 50), Vector2(CENTER_X, CENTER_Y + 100))));
	buttons["Start"]->SetOnClick(bind(&LobbyScene::StartGame, this));
}

LobbyScene::~LobbyScene()

{
	delete backGround;
	for (pair<string, Button*> button : buttons)
	{
		delete button.second;
	}
	buttons.clear();

}

void LobbyScene::Update()
{
	for (auto& button : buttons) {
		button.second->Update();
	}
}

void LobbyScene::Render()
{
	backGround->Render();
	for (auto& button : buttons) {
		button.second->Render();
	}
}

void LobbyScene::GUIRender()
{
}
void LobbyScene::StartGame()
{
	SCENE->ChangeScene("Game");
}