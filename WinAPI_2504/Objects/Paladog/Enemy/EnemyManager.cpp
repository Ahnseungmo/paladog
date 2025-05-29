#include "Framework.h"
#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
	for (int i = 0;i < ENEMY_POOL_SIZE;i++)
	{
		EnemyUnit* enemy = new EnemyUnit("Zombie");
		enemy->SetActive(false);
		enemies["Zombie"].push_back(enemy);
	}
	for (int i = 0;i < ENEMY_POOL_SIZE;i++)
	{
		EnemyUnit* enemy = new EnemyUnit("LadySkeleton");
		enemy->SetActive(false);
		enemies["LadySkeleton"].push_back(enemy);
	}
	for (int i = 0;i < ENEMY_POOL_SIZE;i++)
	{
		EnemyUnit* enemy = new EnemyUnit("Witch");
		enemy->SetActive(false);
		enemies["Witch"].push_back(enemy);
	}
	for (int i = 0;i < ENEMY_POOL_SIZE;i++)
	{
		EnemyUnit* enemy = new EnemyUnit("Frankenstein",{70,100});
		Vector2 pos = enemy->GetLocalPosition();
		enemy->SetClipTransform({pos.x,pos.y+30});
		enemy->SetActive(false);
		enemies["Frankenstein"].push_back(enemy);
	}

	//에너미 데이터값 여기서 인서트하기전에 주고넣자
	//성이랑 보스몬스터 만들기
}

EnemyManager::~EnemyManager()
{
	for (auto& enemy : enemies["Zombie"])
	{
		delete enemy;
	}
	for (auto& enemy : enemies["LadySkeleton"])
	{
		delete enemy;
	}
	for (auto& enemy : enemies["Witch"])
	{
		delete enemy;
	}
	for (auto& enemy : enemies["Frankenstein"])
	{
		delete enemy;
	}
	enemies.clear();
}

void EnemyManager::Update()
{
	for (auto& enemy : enemies["Zombie"])
	{
		if (!enemy->IsActive())
			continue;
		enemy->Update();
	}
	for (auto& enemy : enemies["LadySkeleton"])
	{
		if (!enemy->IsActive())
			continue;
		enemy->Update();
	}
	for (auto& enemy : enemies["Witch"])
	{
		if (!enemy->IsActive())
			continue;
		enemy->Update();
	}
	for (auto& enemy : enemies["Frankenstein"])
	{
		if (!enemy->IsActive())
			continue;
		enemy->Update();
	}
}

void EnemyManager::Render()
{
	for (auto& enemy : enemies["Zombie"])
	{
		if (!enemy->IsActive())
			continue;
		enemy->Render();
	}
	for (auto& enemy : enemies["LadySkeleton"])
	{
		if (!enemy->IsActive())
			continue;
		enemy->Render();
	}
	for (auto& enemy : enemies["Witch"])
	{
		if (!enemy->IsActive())
			continue;
		enemy->Render();
	}
	for (auto& enemy : enemies["Frankenstein"])
	{
		if (!enemy->IsActive())
			continue;
		enemy->Render();
	}
}

void EnemyManager::SetTargetList(vector<Character*>* unit)
{
	for (auto& enemy : enemies["Zombie"])
	{
		if (!enemy->IsActive())
			continue;
		enemy->SetTargetList(unit);
	}
	for (auto& enemy : enemies["LadySkeleton"])
	{
		if (!enemy->IsActive())
			continue;
		enemy->SetTargetList(unit);
	}
	for (auto& enemy : enemies["Witch"])
	{
		if (!enemy->IsActive())
			continue;
		enemy->SetTargetList(unit);
	}
	for (auto& enemy : enemies["Frankenstein"])
	{
		if (!enemy->IsActive())
			continue;
		enemy->SetTargetList(unit);
	}
}

vector<Character*> EnemyManager::GetTargetEnemy()
{
	vector<Character*> myEnemies;

	for (auto& enemy : enemies["Zombie"])
	{
		if (!enemy->IsActive())
			continue;
		myEnemies.push_back(enemy);
	}
	for (auto& enemy : enemies["LadySkeleton"])
	{
		if (!enemy->IsActive())
			continue;
		myEnemies.push_back(enemy);
	}
	for (auto& enemy : enemies["Witch"])
	{
		if (!enemy->IsActive())
			continue;
		myEnemies.push_back(enemy);
	}
	for (auto& enemy : enemies["Frankenstein"])
	{
		if (!enemy->IsActive())
			continue;
		myEnemies.push_back(enemy);
	}
	return myEnemies;
}

void EnemyManager::CreateZombie()
{
	for (auto& enemy : enemies["Zombie"])
	{
		if (enemy->IsActive())
			continue;
		enemy->SetActive(true);
		enemy->SetLocalPosition(RendomPos());
		enemy->SetStat(enemy->GetStat());
		return;
	}
}

void EnemyManager::CreateWitch()
{
	for (auto& enemy : enemies["Witch"])
	{
		if (enemy->IsActive())
			continue;
		enemy->SetActive(true);
		enemy->SetLocalPosition(RendomPos());
		enemy->SetStat(enemy->GetStat());
		return;
	}
}

void EnemyManager::CreateLadySkeleton()
{
	for (auto& enemy : enemies["LadySkeleton"])
	{
		if (enemy->IsActive())
			continue;
		enemy->SetActive(true);
		enemy->SetLocalPosition(RendomPos());
		enemy->SetStat(enemy->GetStat());
		return;
	}
}

void EnemyManager::CreateFrankenstein()
{
	for (auto& enemy : enemies["Frankenstein"])
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
	int x = 1300;
	int y = rand() % 650; // 450 ~ 650 
	if (y < 150)
		y += 400;
	if (y < 400)
		y += 200;
	if (y < 500)
		y += 100;
	return Vector2(x,y);
}


