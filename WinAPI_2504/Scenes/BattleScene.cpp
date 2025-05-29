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

	//enemy = new Enemy_Witch();
	//enemy->SetLocalPosition(Vector2(1100, 500));
	//enemies.push_back(enemy);

	EnemyManager::Get();
	//EnemyManager::Get()->SpawnEnemy("Zombie");
	//EnemyManager::Get()->SpawnEnemy("Witch");
	//EnemyManager::Get()->SpawnEnemy("LadySkeleton");
	//EnemyManager::Get()->SpawnEnemy("Frankenstein");
	EnemyManager::Get()->SpawnEnemy("IronMan");
	//EnemyManager::Get()->SpawnEnemy("Warrior");
	//EnemyManager::Get()->SpawnEnemy("Warrior");

	enemies = EnemyManager::Get()->GetTargetEnemy(); // 활성화 된 애들 가져오기
	EnemyManager::Get()->SetTargetList(&allies); // 에너미의 타겟 설정

	castle = new Enemy_Castle();

	enemies.push_back(castle);
	for (Character* unit : allies)
		unit->SetTargetList(&enemies);

	//for (Character* unit : enemies)
	//	unit->SetTargetList(&allies);


}

BattleScene::~BattleScene()
{
	for (Character* unit : allies)
		delete unit;

	for (Character* unit : enemies)
		delete unit;

	EnemyManager::Delete();

	delete castle;
}

void BattleScene::Update()
{
	for (Character* unit : allies)
		if (unit->IsActive())
			unit->Update();

	for (Character* unit : enemies)
		if (unit->IsActive())
			unit->Update();

	EnemyManager::Get()->Update();

	castle->Update();

	if (castle->GetHP() <= 0) // 성 체력기반으로 죽었는지 확인하고 죽으면 무너진 성 내비두고 타겟 해제돼요
	{
		auto it = find(enemies.begin(), enemies.end(), castle);
		if (it != enemies.end())
		{
			enemies.erase(it);
		}
	}

}

void BattleScene::Render()
{
	for (Character* unit : allies)
		if (unit->IsActive())
			unit->Render();

	for (Character* unit : enemies)
		if (unit->IsActive())
			unit->Render();

	EnemyManager::Get()->Render();

	castle->Render();
}
