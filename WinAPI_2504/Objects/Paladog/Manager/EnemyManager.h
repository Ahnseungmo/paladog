#pragma once

enum class Enemy_Type
{
	Castle =1,
	Fankenstein,
	IronMan,
	LadySkeleton,
	Warrior,
	Witch,
	Zombie,
	Boss
};
class EnemyManager : public Singleton<EnemyManager>
{
	friend class Singleton;
private:
	const int ENEMY_POOL_SIZE = 50;

private:
	EnemyManager();
	~EnemyManager();

public:
	void Update();
	void Render();

	void SetTargetList(vector<Character*>* unit);
	vector<Character*> ActiveUnits();
	vector<Character*>* GetAllUnits();

	void SpawnEnemy(Enemy_Type key);

private:
	template<typename T>
	void CreateEnemies(Enemy_Type key)
	{
		for (int i = 0; i < ENEMY_POOL_SIZE; i++)
		{
			T* enemy = new T;
			enemy->SetActive(false);
			enemies[key].push_back(enemy);
		}
	}

	template<typename T>
	void CreateEnemy(Enemy_Type key)
	{
		T* enemy = new T;
		enemy->SetActive(false);
		enemies[key].push_back(enemy);
	}

	void SpawnBoss();

private:
	Vector2 RendomPos();


private:
	bool isSpawnBoss = false;
	bool isSpawnHalf = false;

	unordered_map<Enemy_Type, vector<Character*>> enemies;
	vector<Character*>* unit;
};