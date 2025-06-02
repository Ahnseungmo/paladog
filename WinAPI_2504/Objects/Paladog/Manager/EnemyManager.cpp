#include "Framework.h"
#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
	CreateEnemy<Enemy_Castle>(Enemy_Type::Castle);
	CreateEnemy<Enemy_Boss>(Enemy_Type::Boss);
	
	CreateEnemies<Enemy_Zombie>(Enemy_Type::Zombie);
	CreateEnemies<Enemy_Frankenstein>(Enemy_Type::Frankenstein);
	CreateEnemies<Enemy_Witch>(Enemy_Type::Witch);
	CreateEnemies<Enemy_LadySkeleton>(Enemy_Type::LadySkeleton);
	CreateEnemies<Enemy_Warrior>(Enemy_Type::Warrior);
	CreateEnemies<Enemy_IronMan>(Enemy_Type::IronMan);

	//성이랑 보스몬스터 만들기

	SetOriginalTime();

	castle = (Enemy_Castle*)enemies[Enemy_Type::Castle][0];
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
	SpawnBossAndEnemy();

	SpawnEnemies();

	for (auto& enemy : enemies)
	{
		for (Character* myEnemy : enemy.second)
		{
			if (!myEnemy->IsActive())
				continue;
			myEnemy->Update();
			EnemyOut(myEnemy);
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

bool EnemyManager::IsCastle(Character* enemy)
{
	if (enemy == castle)
		return true;
	else false;
}

void EnemyManager::ResetEnemy()
{
	for (auto& enemy : enemies)
	{
		for (Character* myEnemy : enemy.second)
		{
			if (!myEnemy->IsActive())
				continue;
			myEnemy->SetActive(false);
			myEnemy->SetStat(myEnemy->GetBaseStat());
		}
	}

	enemies[Enemy_Type::Castle][0]->SetActive(true);

	isSpawnBoss = false;
	isSpawnHalf = false;

	SetOriginalTime();

	timer = 0.0;
}

void EnemyManager::SpawnBossAndEnemy()
{
	int a = castle->GetHP();
	if (castle->GetHP() <= 0 && isSpawnBoss == false)
	{
		isSpawnBoss = true;
		Enemy_Boss* boss = (Enemy_Boss*)enemies[Enemy_Type::Boss][0];
		boss->SetActive(true);
		boss->SetLocalPosition(castle->GetGlobalPosition()); //why boss not find target?
		boss->SetTargetList(unit);

		boss->SpawnBoss();
	
	}
	else if (castle->GetHP() <= castle->GetMaxHP() * 0.5f && isSpawnHalf == false)
	{
		isSpawnHalf = true;
		SpawnEnemy(Enemy_Type::IronMan);
		SpawnEnemy(Enemy_Type::Frankenstein);
		SpawnEnemy(Enemy_Type::Witch);
	}
}

void EnemyManager::SpawnEnemies()
{
	timer += DELTA;

	if (timer - zombieTimer > SPAWN_ZOMBIE_TIME)
	{
		SpawnEnemy(Enemy_Type::Zombie);
		zombieTimer = timer;
	}

	if (timer - witchTimer > SPAWN_WITCH_TIME)
	{
		SpawnEnemy(Enemy_Type::Witch);
		witchTimer = timer;
	}

	if (timer - warriorTimer > SPAWN_WARRIOR_TIME)
	{
		SpawnEnemy(Enemy_Type::Warrior);
		warriorTimer = timer;
	}

	if (timer - ladyskeletonTimer > SPAWN_LADYSKELETON_TIME)
	{
		SpawnEnemy(Enemy_Type::LadySkeleton);
		ladyskeletonTimer = timer;
	}

	if (timer - ironmanTimer > SPAWN_IRONMAN_TIME)
	{
		SpawnEnemy(Enemy_Type::IronMan);
		ironmanTimer = timer;
	}

	if (timer - frankensteinTimer > SPAWN_FRANKENSTEIN_TIME)
	{
		SpawnEnemy(Enemy_Type::Frankenstein);
	}
}

Vector2 EnemyManager::RendomPos()
{
	float x = castle->GetGlobalPosition().x;
	int y = rand() % 200 + 500; // 500 ~ 700 
	return Vector2(x, y);
}

void EnemyManager::EnemyOut(Character* enemy)
{
	Vector2 pos = enemy->GetGlobalPosition();
	if (pos.x > -500)
		return;
	SceneManager::Get()->ChangeScene("GameOver");
}


