#include "Framework.h"
#include "BattleScene.h"

BattleScene::BattleScene()
{
	/*allyK = new Ally_Knight();
	allyK->SetLocalPosition(Vector2(200, 600));
	allies.push_back(allyK);

	allyL = new Ally_Lancer();
	allyL->SetLocalPosition(Vector2(100, 550));
	allies.push_back(allyL);

	allyT = new Ally_Tanker();
	allyT->SetLocalPosition(Vector2(100, 500));
	allies.push_back(allyT);

	allyA = new Ally_Archer();
	allyA->SetLocalPosition(Vector2(100, 450));
	allies.push_back(allyA);

	allyE = new Ally_Elite();
	allyE->SetLocalPosition(Vector2(100, 400));
	allies.push_back(allyE);*/

	allyB = new Ally_Boxer();
	allyB->SetLocalPosition(Vector2(100, 500));
	allies.push_back(allyB);


	/*enemy1 = new EnemyUnit();
	enemy1->SetLocalPosition(Vector2(1200, 500));
	enemies.push_back(enemy1);*/

	enemy = new Enemy_Witch();
	enemy->SetLocalPosition(Vector2(1100, 500));
	enemies.push_back(enemy);

	for (Character* unit : allies)
		unit->SetTargetList(&enemies);

	for (Character* unit : enemies)
		unit->SetTargetList(&allies);
}

BattleScene::~BattleScene()
{
	for (Character* unit : allies)
		delete unit;

	for (Character* unit : enemies)
		delete unit;
}

void BattleScene::Update()
{
	for (Character* unit : allies)
		if (unit->IsActive())
			unit->Update();

	for (Character* unit : enemies)
		if (unit->IsActive())
			unit->Update();
}

void BattleScene::Render()
{
	for (Character* unit : allies)
		if (unit->IsActive())
			unit->Render();

	for (Character* unit : enemies)
		if (unit->IsActive())
			unit->Render();
}
