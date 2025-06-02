#include "Framework.h"
#include "UnitDataPanel.h"

UnitDataPanel::UnitDataPanel(Vector2 pos)
{
	SetLocalPosition(pos);
	UpdateWorld();

	CreateUnitData();
	CreateUnitStatusBar();

	EventManager::Get()->AddEvent("DisplayUnit", bind(&UnitDataPanel::DisplayUnit, this,placeholders::_1));
}

UnitDataPanel::~UnitDataPanel()
{
	for (auto& button : buttons)
		delete button;
	buttons.clear();

	for (auto& unit : unitTexture)
		delete unit.second;
	unitTexture.clear();


}


void UnitDataPanel::Update()
{
	UpdateWorld();
	for (auto button : buttons)
		button->Update();

}

void UnitDataPanel::Render()
{
	for (auto button : buttons)
		button->Render();
	for (auto& unit : unitTexture)
		unit.second->Render();
	for (auto& unit : unitStatusBar)
		unit->Render();
}

void UnitDataPanel::CreateUnitData()
{
	auto unitData = DataManager::Get()->GetAllyDatas().begin();
	for (; unitData != DataManager::Get()->GetAllyDatas().end(); unitData++) {
//		if (bagData->first == 1) continue;
		unitTexture.insert(make_pair(unitData->first, new Quad(unitImages[unitData->first], Vector2{ 0,0 }, Vector2({1.0f,1.0f}))));
		unitTexture.at(unitData->first)->SetLocalPosition(Vector2(50, 150));
		unitTexture.at(unitData->first)->SetParent(this);
		unitTexture.at(unitData->first)->SetActive(false);
		unitTexture.at(unitData->first)->UpdateWorld();
	}

}
void UnitDataPanel::CreateUnitStatusBar()
{
	Vector2 pos = Vector2{ 382,-90 };
	for(int i=0;i<4;i++){
		unitStatusBar.push_back(new Quad(L"Resources/Textures/Paladog/Unit/UnitStatusBar.png", Vector2{ 0,0 }, Vector2({ 1.0f,1.0f })));
		unitStatusBar.back()->SetLocalPosition(pos + Vector2(0,i*UnitStatusBarPadding));
		unitStatusBar.back()->SetParent(this);

		unitStatusBar.back()->SetActive(false);
		unitStatusBar.back()->UpdateWorld();
	}

}

void UnitDataPanel::DisplayUnit(void* keydata)
{
	int key = static_cast<int>(reinterpret_cast<intptr_t>(keydata));
	for (auto& unit : unitTexture) {
		unit.second->SetActive(false);
	}
	for (auto& unit : unitStatusBar) {
		unit->SetActive(true);
	}


	if (unitImages.find(key) != unitImages.end()) {
		unitTexture[key]->SetActive(true);

		int i = 0;
		BagData& bagData = DataManager::Get()->GetBag(key);
		AllyData allyData = DataManager::Get()->GetAllyDatas().at(key);
		CharacterData characterData = DataManager::Get()->GetCharacter(key);
		for (auto& unit : unitStatusBar) {
			float xScale;
			switch (i++) {
			case 0:
				xScale = (characterData.baseHp + allyData.hpPerLevel * (bagData.level-1)) / 1000.0f;
				break;
			case 1:
				xScale = (characterData.baseAttack + allyData.attackPerLevel * (bagData.level - 1)) / 200.0f;
				break;
			case 2:
				xScale = (characterData.baseSpeed + allyData.speedPerLevel * (bagData.level - 1)) / 500.0f;
				break;
			case 3:
				xScale = (characterData.baseAttackSpeed + allyData.attackSpeedPerLevel * (bagData.level - 1)) / 10.0f;
				break;
			}

			unit->SetPivot(0.0f, 0.0f);

			unit->SetSize({ BAR_WIDTH * xScale, 10 });
			unit->SetLocalPosition(Vector2(382 - (BAR_WIDTH-(BAR_WIDTH*xScale))/2, unit->GetLocalPosition().y));

			unit->SetActive(true);
			unit->UpdateWorld();
			unit->Render();
		}

	}

}
