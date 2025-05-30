#include "Framework.h"
#include "GotchaScene.h"

GotchaScene::GotchaScene()
{
	backGround = new Quad(L"Resources/Textures/Paladog/LobbyBackGround.png", Vector2(0, 0), Vector2(1.0f, 1.0f));
	backGround->SetLocalPosition(CENTER);
	backGround->UpdateWorld();

	backGround = new Quad(L"Resources/Textures/Paladog/LobbyBackGround.png", Vector2(0, 0), Vector2(1.0f, 1.0f));
	backGround->SetLocalPosition(CENTER);
	backGround->UpdateWorld();

	chest = new Chest();
	chest->SetLocalPosition(CENTER);
	chest->UpdateWorld();

	buttons.insert(make_pair("Gotcha1", new Button(L"Resources/Textures/Paladog/Lobby/btn_hero_up.png", Vector2(100, 50), Vector2(CENTER_X, CENTER_Y - 300))));
	buttons["Gotcha1"]->SetOnClick(bind(&GotchaScene::Gotcha, this));
	buttons["Gotcha1"]->Update();


	buttons.insert(make_pair("Gotcha", new Button(L"Resources/Textures/Paladog/Lobby/btn_hero_up.png", Vector2(100, 50), Vector2(100, SCREEN_HEIGHT - 300))));
	buttons["Gotcha"]->SetOnClick(bind(&GotchaScene::Lobby, this));
	buttons["Gotcha"]->Update();

}

GotchaScene::~GotchaScene()

{
	delete backGround;
	for (pair<string, Button*> button : buttons)
	{
		delete button.second;
	}
	buttons.clear();
	delete chest;
}

void GotchaScene::Update()
{
	for (auto& button : buttons) {
		button.second->Update();
	}

	chest->Update();
}

void GotchaScene::Render()
{
	backGround->Render();
	for (auto& button : buttons) {
		button.second->Render();
	}
	chest->Render();
}

void GotchaScene::GUIRender()
{

}

void GotchaScene::Lobby()
{
	chest->ChestIdle();

	SCENE->ChangeScene("Lobby");
}


void GotchaScene::Gotcha()
{
	chest->ChestOpen();
	int firstKey = DataManager::Get()->GetMinionDatas().begin()->first;
//	int eneKey = DataManager::Get()->GetMinionDatas().end()->first;
	int pickKey = firstKey + rand() % DataManager::Get()->GetMinionCount();
	if (DataManager::Get()->GetBagDatas().count(pickKey)) {
		BagData& bagData = DataManager::Get()->GetBag(pickKey);
		bagData.count++;
//		bagData.level++;

	}
	else {
		BagData bagData;
		bagData.key = pickKey;
		bagData.count = 1;
		bagData.level = 1;

		DataManager::Get()->GetBagDatas().insert({ pickKey,bagData });
	}
	
	chest;
}
