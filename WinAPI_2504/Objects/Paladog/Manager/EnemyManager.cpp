#include "Framework.h"
#include "EnemyManager.h"

EnemyManager::EnemyManager()
{

	CreateEnemy<Enemy_Castle>(Enemy_Type::Castle);
	CreateEnemy<Enemy_Boss>(Enemy_Type::Boss);
	
	CreateEnemies<Enemy_Zombie>(Enemy_Type::Zombie);
	CreateEnemies<Enemy_Frankenstein>(Enemy_Type::Fankenstein);
	CreateEnemies<Enemy_Witch>(Enemy_Type::Witch);
	CreateEnemies<Enemy_LadySkeleton>(Enemy_Type::LadySkeleton);
	CreateEnemies<Enemy_Warrior>(Enemy_Type::Warrior);
	CreateEnemies<Enemy_IronMan>(Enemy_Type::IronMan);

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

vector<Character*> EnemyManager::ActiveUnits()
{
	vector<Character*> result;

	unordered_map<Enemy_Type, vector<Character*>>::iterator it;
	for (it = enemies.begin(); it != enemies.end(); ++it)
	{
		vector<Character*>& enemyList = it->second;
		for (int i = 0; i < enemyList.size(); ++i)
		{
			if (enemyList[i]->IsActive())
				result.push_back(enemyList[i]);
		}
	}

	return result;
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

	unordered_map<Enemy_Type, vector<Character*>>::iterator it;
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

void EnemyManager::SpawnEnemy(Enemy_Type key)
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
	Character* castle = enemies[Enemy_Type::Castle][0];

	if (castle->GetHP() <= 0 && isSpawnBoss == false)
	{
		isSpawnBoss = true;
		Enemy_Boss* boss = (Enemy_Boss*)enemies[Enemy_Type::Castle][0];
		boss->SetActive(true);
		boss->SetLocalPosition(castle->GetGlobalPosition()); //why boss not find target?
		boss->SetTargetList(unit);

		boss->SpawnBoss();
	
	}
	else if (castle->GetHP() <= 50 && isSpawnHalf == false)
	{
		isSpawnHalf = true;
		SpawnEnemy(Enemy_Type::IronMan);
		SpawnEnemy(Enemy_Type::Fankenstein);
		SpawnEnemy(Enemy_Type::Witch);
	}
}

Vector2 EnemyManager::RendomPos()
{
	Character* castle = enemies[Enemy_Type::Castle][0];
	float x = castle->GetGlobalPosition().x;
	int y = rand() % 200 + 450; // 450 ~ 650 
	return Vector2(x, y);
}


