#include "Framework.h"
#include "IntroScene.h"

IntroScene::IntroScene()
{
	wstring path = L"Resources/Textures/Paladog/Title/title_back.png";

	backGround = new Quad(path, Vector2(0, 0), Vector2(1.0f, 1.0f));

	backGround->SetLocalPosition(CENTER);
	backGround->UpdateWorld();

	buttons.insert(make_pair("Start", new Button(L"Resources/Textures/Paladog/Title/title_btn.png", Vector2(296, 200), Vector2(198, 100))));
	buttons["Start"]->SetOnClick(bind(&IntroScene::Start, this));
	//	buttons["Start"]->SetLocalPosition(buttons["Start"]->Size());
	buttons["Start"]->Update();

	DataManager::Get()->LoadCharacterData("Resources/Tables/CharacterTable.csv");
	DataManager::Get()->LoadAllyData("Resources/Tables/AllyTable.csv");
	DataManager::Get()->LoadEnemyData("Resources/Tables/EnemyTable.csv");
	DataManager::Get()->LoadBagData("Resources/Tables/BagTable.csv");
	DataManager::Get()->LoadDeckData("Resources/Tables/DeckTable.csv");



}

IntroScene::~IntroScene()
{
	delete backGround;

}

void IntroScene::Update()
{
	if (!isBooting && bootTimer > BOOT_TIME) isBooting = true;
	else bootTimer += DELTA;
	if (!isBooting) return;

	for (auto& button : buttons) {
		button.second->Update();
	}

}

void IntroScene::Render()
{
	backGround->Render();
	for (auto& button : buttons) {
		button.second->Render();
	}
}

void IntroScene::GUIRender()
{
}

void IntroScene::Start() {
	if (!isBooting) return;
	SceneManager::Get()->ChangeScene("Lobby");
}