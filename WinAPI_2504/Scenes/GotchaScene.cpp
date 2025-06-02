#include "Framework.h"
#include "GotchaScene.h"

GotchaScene::GotchaScene()
{
	backGround = new Quad(L"Resources/Textures/Paladog/Gotcha/BackGround.png", Vector2(0, 0), Vector2(1.0f, 1.0f));
	backGround->SetLocalPosition(CENTER);
	backGround->UpdateWorld();

	chest = new Chest();
	chest->SetLocalPosition(CENTER);
	chest->UpdateWorld();
	chest->Update();

	buttons.insert(make_pair("Gotcha1", new Button(L"Resources/Textures/Paladog/Lobby/btn_hero_up.png", Vector2(100, 50), Vector2(CENTER_X, CENTER_Y - 300))));
	buttons["Gotcha1"]->SetOnClick(bind(&GotchaScene::Gotcha, this));
	buttons["Gotcha1"]->Update();


	buttons.insert(make_pair("Gotcha", new Button(L"Resources/Textures/Paladog/Lobby/btn_hero_up.png", Vector2(100, 50), Vector2(100, SCREEN_HEIGHT - 300))));
	buttons["Gotcha"]->SetOnClick(bind(&GotchaScene::Lobby, this));
	buttons["Gotcha"]->Update();

	//	Vector2 quadSize(100, 100);
	Vector2 quadSize(0, 0);
	Transform* quadTransform = new Transform();
	quadTransform->SetLocalPosition(Vector2(CENTER_X,CENTER_Y+300));

	quadTransform->UpdateWorld();
	characterQuads.insert(make_pair(1001, new Quad(L"Resources/Textures/Paladog/Gotcha/Character/Knight.png", quadSize, Vector2(1.0f, 1.0f))));
	characterQuads.insert(make_pair(1002, new Quad(L"Resources/Textures/Paladog/Gotcha/Character/Archer.png", quadSize, Vector2(1.0f, 1.0f))));
	characterQuads.insert(make_pair(1003, new Quad(L"Resources/Textures/Paladog/Gotcha/Character/Boxer.png", quadSize, Vector2(1.0f, 1.0f))));
	characterQuads.insert(make_pair(1004, new Quad(L"Resources/Textures/Paladog/Gotcha/Character/Lancer.png", quadSize, Vector2(1.0f, 1.0f))));
	characterQuads.insert(make_pair(1005, new Quad(L"Resources/Textures/Paladog/Gotcha/Character/Tanker.png", quadSize, Vector2(1.0f, 1.0f))));
	characterQuads.insert(make_pair(1006, new Quad(L"Resources/Textures/Paladog/Gotcha/Character/Elite.png", quadSize, Vector2(1.0f, 1.0f))));
	characterQuads.insert(make_pair(1007, new Quad(L"Resources/Textures/Paladog/Gotcha/Character/Bomber.png", quadSize, Vector2(1.0f, 1.0f))));

	for (auto& quad : characterQuads) {
		quad.second->SetParent(quadTransform);
		quad.second->SetSize({ 100,100 });
		quad.second->SetLocalScale({5,5});
		quad.second->SetActive(false);		
		quad.second->UpdateWorld();
	}
	pickCharcterIndex = 0;

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
	if(chest->IsOpenEnd()){
		characterQuads[pickCharcterIndex]->SetActive(true);
	}

	for (auto& quad : characterQuads)
		quad.second->UpdateWorld();

}

void GotchaScene::Render()
{
	backGround->Render();
	for (auto& button : buttons) {
		button.second->Render();
	}
	chest->Render();
	for (auto& quad : characterQuads)
		quad.second->Render();
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
	for (auto quad : characterQuads)
		quad.second->SetActive(false);

	//	int firstKey = DataManager::Get()->GetAllyDatas().begin()->first;
	//	int eneKey = DataManager::Get()->GetMinionDatas().end()->first;
	int pickKey = rand() % DataManager::Get()->GetAllyCount();
	auto it = DataManager::Get()->GetAllyDatas().begin();

	for (int i = 0; i < pickKey; i++) {
		it++;
	}
	int isData = false;
	for (auto data : DataManager::Get()->GetBagDatas()) {
		if (data.first == it->first) {
			isData = true;
			break;
		}
	}
	if (isData) {
		BagData& bagData = DataManager::Get()->GetBag(it->first);
		bagData.count++;
	}
	else {
		BagData bagData;
		bagData.key = it->first;
		bagData.name = it->second.name;
		bagData.count = 1;
		bagData.level = 1;
		DataManager::Get()->GetBagDatas().insert(make_pair(it->first, bagData));

	}
	pickCharcterIndex = it->first;

}