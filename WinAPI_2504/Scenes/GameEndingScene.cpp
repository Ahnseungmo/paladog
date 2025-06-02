#include "Framework.h"
#include "GameEndingScene.h"

GameEndingScene::GameEndingScene(wstring filePath)
{
	backGround = new Quad(filePath, Vector2(0, 0), Vector2(1.0f, 1.0f));

	backGround->SetLocalPosition(CENTER);
	backGround->UpdateWorld();

	button = new Button(L"Resources/Textures/Paladog/Lobby/btn_ui_battle_up.png", Vector2(200, 100), Vector2(198, 100));
	button->SetLocalScale({ 1.2,1.2 });

	button->SetOnClick(bind(&GameEndingScene::ReStart, this));
	button->Update();
	//buttons.insert(make_pair("Start", new Button(L"Resources/Textures/Paladog/Title/title_btn.png", Vector2(296, 200), Vector2(198, 100))));
	//buttons["Start"]->SetOnClick(bind(&IntroScene::Start, this));
	////	buttons["Start"]->SetLocalPosition(buttons["Start"]->Size());
	//buttons["Start"]->Update();

}

GameEndingScene::~GameEndingScene()
{
	delete backGround;
}

void GameEndingScene::Update()
{
	button->Update();
}

void GameEndingScene::Render()
{
	backGround->Render();
	button->Render();
}

void GameEndingScene::ReStart()
{
	SceneManager::Get()->ChangeScene("Lobby");
}
