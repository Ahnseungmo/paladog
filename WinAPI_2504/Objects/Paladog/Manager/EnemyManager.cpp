#include "Framework.h"
#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
	castle = new Enemy_Castle();
	castle->SetLocalPosition(Vector2{ CENTER });
	enemies["Castle"].push_back(castle);
	
	CreateEnemy<Enemy_Zombie>("Zombie");
	CreateEnemy<Enemy_Frankenstein>("Frankenstein");
	CreateEnemy<Enemy_Witch>("Witch");
	CreateEnemy<Enemy_LadySkeleton>("LadySkeleton");
	CreateEnemy<Enemy_Warrior>("Warrior");
	CreateEnemy<Enemy_IronMan>("IronMan");

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
		return;
	}
}

Vector2 EnemyManager::RendomPos()
{
	float x = 1300.0f;
	int y = rand() % 200 + 450; // 450 ~ 650 
	return Vector2(x, y);
}


