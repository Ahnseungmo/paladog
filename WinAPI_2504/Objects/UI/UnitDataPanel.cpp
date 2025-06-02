#include "Framework.h"
#include "UnitDataPanel.h"

UnitDataPanel::UnitDataPanel(Vector2 pos)
{
	SetLocalPosition(pos);
	UpdateWorld();

	CreateUnitData();
	CreateUnitStatusBar();
	textUnitCount = new TextBox(Vector2(-100, -130), Vector2(200, 380), "1");
	textUnitCount->SetFont("Resources/Fonts/NanumBarunGothic.ttf");
	textUnitCount->SetFontSize(50);
	textUnitCount->SetParent(this);
	textUnitCount->UpdateWorld();

	textUnitLevelCost = new TextBox(Vector2(300, -120), Vector2(200, 400), "1");
	textUnitLevelCost->SetFont("Resources/Fonts/NanumBarunGothic.ttf");
	textUnitLevelCost->SetFontSize(50);
	textUnitLevelCost->SetParent(this);
	textUnitLevelCost->UpdateWorld();

	textUnitExplane = new TextBox(Vector2(-100, -200), Vector2(500, 400), "1");
	textUnitExplane->SetFont("Resources/Fonts/NanumBarunGothic.ttf");
	textUnitExplane->SetFontSize(50);
	textUnitExplane->SetParent(this);
	textUnitExplane->UpdateWorld();

	textUnitLevel = new TextBox(Vector2(0, -20), Vector2(200, 450), "LV");
	textUnitLevel->SetFont("Resources/Fonts/NanumBarunGothic.ttf");
	textUnitLevel->SetFontSize(50);
	textUnitLevel->SetParent(this);
	textUnitLevel->UpdateWorld();

	string text = to_string(DataManager::Get()->GetBagDatas().at(1).count);
	textMoney = new TextBox(Vector2(200, 100) - Vector2(GetGlobalPosition()), Vector2(200, 400), text.c_str());
	textMoney->SetFont("Resources/Fonts/NanumBarunGothic.ttf");
	textMoney->SetFontSize(50);
	textMoney->SetParent(this);
	textMoney->UpdateWorld();

	buttons.push_back(new Button(L"Resources/Textures/Paladog/Unit/btn_upgrade_up.png", Vector2(235,74), Vector2(70, -150)));
	buttons.back()->SetParent(this);
	buttons.back()->SetOnClick(bind(&UnitDataPanel::UnitUpgrade, this));

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

	for(int i=0;i<2;i++)
		for (auto& unit : unitTextureSmall[i])
			delete unit.second;
	unitTextureSmall[0].clear();
	unitTextureSmall[1].clear();

	delete textUnitCount;
	delete textUnitLevelCost;
	delete textUnitExplane;
	delete textUnitLevel;
	delete textMoney;
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
	for(int i=0;i<2;i++)
		for (auto& unit : unitTextureSmall[i])
			unit.second->Render();

	textUnitCount->Render();
	textUnitLevelCost->Render();
	textUnitExplane->Render();
	textUnitLevel->Render();
	textMoney->Render();
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
		for (int i = 0; i < 2; i++) {
			unitTextureSmall[i].insert(make_pair(unitData->first, new Quad(unitImages[unitData->first], Vector2{0,0}, Vector2({1.0f,1.0f}))));
			unitTextureSmall[i].at(unitData->first)->SetLocalPosition(Vector2(-125 + i*600, -125 + i * 10));
			unitTextureSmall[i].at(unitData->first)->SetParent(this);
			unitTextureSmall[i].at(unitData->first)->SetLocalScale(Vector2(0.3f, 0.3f));
			unitTextureSmall[i].at(unitData->first)->SetActive(false);
			unitTextureSmall[i].at(unitData->first)->UpdateWorld();
		}

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
	selKey = key;
	for (auto& unit : unitTexture) {
		unit.second->SetActive(false);
	}
	for(int i=0;i<2;i++)
		for (auto& unit : unitTextureSmall[i]) {
			unit.second->SetActive(false);
		}

	for (auto& unit : unitStatusBar) {
		unit->SetActive(true);
	}

	textUnitCount->SetText(to_string(DataManager::Get()->GetBag(key).count).c_str());
	textUnitLevelCost->SetText(to_string(DataManager::Get()->GetBag(key).level * DataManager::Get()->GetAlly(key).cost * 100).c_str());
	textUnitExplane->SetText((DataManager::Get()->GetCharacter(key).name+ "\n\n" + DataManager::Get()->GetCharacter(key).explane).c_str());
	textUnitLevel->SetText(("LV " + to_string(DataManager::Get()->GetBag(key).level)).c_str());
	textMoney->SetText(to_string(DataManager::Get()->GetBag(1).count).c_str());
	if (unitImages.find(key) != unitImages.end()) {
		unitTexture[key]->SetActive(true);
		unitTextureSmall[0].at(key)->SetActive(true);
		unitTextureSmall[1].at(key)->SetActive(true);

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

void UnitDataPanel::UnitUpgrade() {
	BagData& bagData = DataManager::Get()->GetBag(selKey);
	if (bagData.level >= 10) return; // 최대 레벨 10
	if (bagData.count <= 0) return; // 유닛이 없으면 업그레이드 불가
	int cost = bagData.level * DataManager::Get()->GetAlly(selKey).cost * 100;
	int money = DataManager::Get()->GetBag(1).count;
	if (money < cost) return; // 돈이 부족하면 업그레이드 불가
	// 업그레이드
	bagData.level++;
	bagData.count--;
	DataManager::Get()->GetBagDatas().at(1).count = money - cost;

	DisplayUnit((void*)selKey);

}