#include "Framework.h"
#include "LobbyScene.h"

LobbyScene::LobbyScene()
{
	backGround = new Quad(L"Resources/Textures/Paladog/Lobby/LobbyBack.png", Vector2(0, 0), Vector2(1.0f, 1.0f));
	backGround->SetLocalPosition(CENTER);
	backGround->UpdateWorld();

	float buttonY[4] = {};
	buttonY[0] = CENTER_Y;
	for (int i = 1;i < 4;i++) {
		buttonY[i] = buttonY[i - 1] - BUTTON_PADDING;
	}

	buttons.insert(make_pair("Battle", new Button(L"Resources/Textures/Paladog/buttons/Battle.png", Vector2(330, 108), Vector2(CENTER_X, buttonY[0]))));
	buttons.insert(make_pair("Gotcha", new Button(L"Resources/Textures/Paladog/buttons/Gotcha.png", Vector2(330, 108), Vector2(CENTER_X, buttonY[1]))));
	buttons.insert(make_pair("Unit", new Button(L"Resources/Textures/Paladog/buttons/Unit.png", Vector2(330, 108), Vector2(CENTER_X, buttonY[2]))));
	buttons.insert(make_pair("Hero", new Button(L"Resources/Textures/Paladog/buttons/Hero.png", Vector2(330, 108), Vector2(CENTER_X, buttonY[3]))));
	for (auto& button : buttons) {
		button.second->SetLocalScale(Vector2(0.7f, 0.7f));
	}

	buttons["Battle"]->SetOnClick(bind(&LobbyScene::Battle, this));
	buttons["Gotcha"]->SetOnClick(bind(&LobbyScene::Gotcha, this));
	buttons["Unit"]->SetOnClick(bind(&LobbyScene::Unit, this));
	buttons["Hero"]->SetOnClick(bind(&LobbyScene::Hero, this));

	buttons["Battle"]->Update();
	buttons["Gotcha"]->Update();
	buttons["Unit"]->Update();
	buttons["Hero"]->Update();

	buttons["Hero"]->SetActive(false);

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
void LobbyScene::Battle()
{
	SCENE->ChangeScene("Battle");
}
void LobbyScene::Gotcha()
{
	//	SCENE->ChangeScene("Shop");
	SCENE->ChangeScene("Gotcha");
}
void LobbyScene::Unit()
{
	SCENE->ChangeScene("Unit");
}
void LobbyScene::Hero()
{
	SCENE->ChangeScene("Hero");
}