#include "Framework.h"
#include "UnitPanel.h"

UnitPanel::UnitPanel(Vector2 pos)
{
	SetLocalPosition(pos);
	UpdateWorld();

	CreateButtons();

	textBox = new TextBox(Vector2(100, 100), Vector2(200, 400), L"Unit PaneUnit PaneUnit PaneUnit PaneUnit Panel");
	textBox->SetParent(this);
}

UnitPanel::~UnitPanel()
{
	for (auto& button : buttons)
		delete button;
	buttons.clear();

}


void UnitPanel::Update()
{
	UpdateWorld();
	for (auto button : buttons)
		button->Update();
	for (auto& check : checkUnits)
		check.second->UpdateWorld();

}

void UnitPanel::Render()
{
	for (auto button : buttons)
		button->Render();
	for (auto& check : checkUnits)
//		if (check.second->IsActive())
			check.second->Render();
	textBox->Render();
}

void UnitPanel::CreateButtons()
{
	int buttonCount = 10;
	float buttonWidth = 120.0f;
	float buttonHeight = 120.0f;
	float buttonSpacing = 5.0f;

	auto bagData = DataManager::Get()->GetBagDatas().begin();
	for (auto& check : checkUnits)
		delete check.second;
	checkUnits.clear();

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			if (bagData == DataManager::Get()->GetBagDatas().end())	return;
			if (bagData->first == 1) {
				j--;
				bagData++;
				continue;
			}
			float x = (buttonWidth + buttonSpacing) * j + (buttonWidth / 2);
			float y = -(buttonHeight + buttonSpacing) * i + (buttonHeight / 2);

			Button* button = new Button(unitImages[bagData->first], Vector2(100, 100), Vector2(x, y));
			button->SetParent(this);

//			button->SetOnClick(bind(&UnitDataPanel::DisplayUnit, parentScene->GetUnitDataPanel()->DisplayUnit((void*) bagData->first)));
			int key = bagData->first;
			int* keyPtr = new int(key);  // 메모리 할당

			button->SetOnClickInt(bind(&UnitPanel::SelectUnit, this,placeholders::_1));
			button->SetIntParameter(key);

			button->SetOnClickRInt(bind(&UnitPanel::EquipUnit, this, placeholders::_1));
			button->SetIntParameterR(key);

			button->UpdateWorld();

			checkUnits.insert(make_pair(key,new Quad(L"Resources/Textures/Paladog/Unit/Check.png", Vector2(0, 0), Vector2(1.0f, 1.0f))));
			checkUnits.at(key)->SetParent(button);
			checkUnits.at(key)->SetLocalPosition(Vector2(0, 0));
			checkUnits.at(key)->SetActive(false);

			vector<int>& deck = DataManager::Get()->GetDeck();
			for (auto& deckData : deck) {
				if (deckData == key) {
					checkUnits[key]->SetActive(true);
					break;
				}
			}
			checkUnits.at(key)->UpdateWorld();
			buttons.push_back(button);
			bagData++;
		}
	}
}
void UnitPanel::SelectUnit(int key)
{
	EventManager::Get()->ExcuteEvent("DisplayUnit", reinterpret_cast<void*>(static_cast<intptr_t>(key)));
}
void UnitPanel::EquipUnit(int key)
{
//	EventManager::Get()->ExcuteEvent("DisplayUnit", reinterpret_cast<void*>(static_cast<intptr_t>(key)));
	vector<int>& deck = DataManager::Get()->GetDeck();
	for (int i = 0; i < DataManager::Get()->GetDeck().size();i++) {
		if (deck[i] == key) {
			CheckEquipUnit(key, false);
			deck.erase(deck.begin() + i);
			return;
		}
	}
	DataManager::Get()->GetDeck().push_back(key);
	CheckEquipUnit(key, true);

}
void UnitPanel::CheckEquipUnit(int key,bool check) {
	vector<int>& deck = DataManager::Get()->GetDeck();

	for (auto& deckData : deck) {
		if (deckData == key) {
			checkUnits[key]->SetActive(check);
			checkUnits[key]->UpdateWorld();
//			checkUnits[key]->Render();
			return;
		}
	}
}

