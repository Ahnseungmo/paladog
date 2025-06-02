#include "Framework.h"
#include "UnitScene.h"

UnitScene::UnitScene()
{
	backGround = new Quad(L"Resources/Textures/Paladog/Unit/unit_back.png", Vector2(0, 0), Vector2(1.0f, 1.0f));
	backGround->SetLocalPosition(CENTER);
	backGround->UpdateWorld();

	buttons.insert(make_pair("Lobby", new Button(L"Resources/Textures/Paladog/Lobby/btn_ui_battle_up.png", Vector2(100, 50), Vector2(SCREEN_WIDTH - 100, SCREEN_HEIGHT - 50))));
	buttons["Lobby"]->SetOnClick(bind(&UnitScene::Lobby, this));
	buttons["Lobby"]->Update();

	unitPanel = new UnitPanel(Vector2(100, 550));
//	unitPanel->SetParent(this);
	unitPanel->UpdateWorld();

	unitDataPanel = new UnitDataPanel(Vector2(700, 500));
	unitDataPanel->UpdateWorld();

}

UnitScene::~UnitScene()
{
	delete backGround;
}
void UnitScene::Start()
{
	unitPanel = new UnitPanel(Vector2(100, 550));
	unitPanel->UpdateWorld();

}
void UnitScene::End() {
	DataManager::Get()->SaveBagData ("Resources/Tables/BagTable.csv");
	DataManager::Get()->SaveDeckData("Resources/Tables/DeckTable.csv");
	delete unitPanel;
	unitPanel = nullptr;
}

void UnitScene::Update()
{
	for (auto& button : buttons) {
		button.second->Update();
	}
	if(unitPanel != nullptr)
		unitPanel->Update();
	unitDataPanel->Update();

}

void UnitScene::Render()
{
	backGround->Render();

	for (auto& button : buttons) {
		button.second->Render();
	}
	if (unitPanel != nullptr)
		unitPanel->Render();

	if (unitDataPanel != nullptr)
		unitDataPanel->Render();
}

void UnitScene::GUIRender()
{
}

void UnitScene::Lobby()
{
	SCENE->ChangeScene("Lobby");

}
void UnitScene::DisplayUnit(int key) {
	if (unitPanel == nullptr)
	{
		return;
	}
}
