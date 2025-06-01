#include "Framework.h"
#include "EnemyManager.h"

EnemyManager::EnemyManager()
{

	CreateEnemy<Enemy_Castle>("Castle");
	CreateEnemy<Enemy_Boss>("Boss");
	
	CreateEnemies<Enemy_Zombie>("Zombie");
	CreateEnemies<Enemy_Frankenstein>("Frankenstein");
	CreateEnemies<Enemy_Witch>("Witch");
	CreateEnemies<Enemy_LadySkeleton>("LadySkeleton");
	CreateEnemies<Enemy_Warrior>("Warrior");
	CreateEnemies<Enemy_IronMan>("IronMan");

	//성이랑 보스몬스터 만들기
}

EnemyManager::~EnemyManager()
{
	for (auto& enemy : enemies)
	{
		for (Character* myEnemy : enemy.second)
		{
			delete myEnemy;
		}
	}

	enemies.clear();
}

void EnemyManager::Update()
{
	SpawnBoss();

	for (auto& enemy : enemies)
	{
		for (Character* myEnemy : enemy.second)
		{
			if (!myEnemy->IsActive())
				continue;
			myEnemy->Update();
		}
	}
}

void EnemyManager::Render()
{
	for (auto& enemy : enemies)
	{
		for (Character* myEnemy : enemy.second)
		{
			if (!myEnemy->IsActive())
				continue;
			myEnemy->Render();
		}
	}
}

void EnemyManager::SetTargetList(vector<Character*>* unit)
{
	this->unit = unit;
	for (auto& enemy : enemies)
	{
		for (Character* myEnemy : enemy.second)
		{
			if (!myEnemy->IsActive())
				continue;
			myEnemy->SetTargetList(unit);
		}
	}


}

//vector<Character*> EnemyManager::GetTargetEnemy()
//{
//	vector<Character*> myEnemies;
//
//	for (auto& enemy : enemies)
//	{
//		for (Character* myEnemy : enemy.second)
//		{
//			if (!myEnemy->IsActive())
//				continue;
//			myEnemies.push_back(myEnemy);
//		}
//	}
//	return myEnemies;
//}

vector<Character*>* EnemyManager::GetAllUnits()
{
	static vector<Character*> allUnits;
	allUnits.clear();

	unordered_map<string, vector<Character*>>::iterator it;
	for (it = enemies.begin(); it != enemies.end(); ++it)
	{
		vector<Character*>& units = it->second;
		for (int i = 0; i < units.size(); i++)
		{
			allUnits.push_back(units[i]);
		}
	}

	return &allUnits;
}

void EnemyManager::SpawnEnemy(string key)
{
	for (auto& enemy : enemies[key])
	{
		if (enemy->IsActive())
			continue;
		enemy->SetActive(true);
		enemy->SetLocalPosition(RendomPos());
		enemy->SetStat(enemy->GetStat());
		enemy->SetTargetList(unit);
		return;
	}
}

void EnemyManager::SpawnBoss()
{
	Character* castle = enemies["Castle"][0];
	
	if (castle->GetHP() <= 0 && isSpawnBoss == false)
	{
		isSpawnBoss = true;
		Enemy_Boss* boss = (Enemy_Boss*)enemies["Boss"][0];
		boss->SetActive(true);
		boss->SetLocalPosition(castle->GetGlobalPosition()); //why boss not find target?
		boss->SetTargetList(unit);

		boss->PushTarget();
	
	}
}

Vector2 EnemyManager::RendomPos()
{
	float x = 1300.0f;
	int y = rand() % 100 + 450; // 450 ~ 650 
	return Vector2(x, y);
}


