#include "Framework.h"
#include "BattleScene.h"

BattleScene::BattleScene()
{
	ally = new Ally_Knight();
	ally->SetLocalPosition(Vector2(200, 600));
	allies.push_back(ally);

	ally1 = new Ally_Knight();
	ally1->SetLocalPosition(Vector2(100, 580));
	UnitStat stat = { 100,20,100,1.0f,500,1 };
	ally1->SetStat(stat);
	allies.push_back(ally1);

	enemy1 = new EnemyUnit();
	enemy1->SetLocalPosition(Vector2(1200, 500));
	enemies.push_back(enemy1);

	enemy = new EnemyUnit();
	enemy->SetLocalPosition(Vector2(1100, 520));
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
