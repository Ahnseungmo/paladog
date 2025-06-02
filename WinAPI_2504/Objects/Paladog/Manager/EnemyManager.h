#pragma once

enum class Enemy_Type
{
	Castle =1,
	Frankenstein,
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

	const float SPAWN_ZOMBIE_TIME = 5.0f;
	const float SPAWN_WITCH_TIME = 20.0f;
	const float SPAWN_WARRIOR_TIME = 23.0f;
	const float SPAWN_LADYSKELETON_TIME = 18.0f;
	const float SPAWN_IRONMAN_TIME = 30.0f;
	const float SPAWN_FRANKENSTEIN_TIME = 50.0f;


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
	bool IsCastle(Character* enemy);

	void ResetEnemy();

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

	void SpawnBossAndEnemy();
	
	void SpawnEnemies();

	void SetOriginalTime()
	{
		zombieTimer = SPAWN_ZOMBIE_TIME;
		witchTimer = SPAWN_WITCH_TIME;
		warriorTimer = SPAWN_WARRIOR_TIME;
		ladyskeletonTimer = SPAWN_LADYSKELETON_TIME;
		ironmanTimer = SPAWN_IRONMAN_TIME;
		frankensteinTimer = SPAWN_FRANKENSTEIN_TIME;
	}

	Vector2 RendomPos();

	void EnemyOut(Character* enemy);

private:
	bool isSpawnBoss = false;
	bool isSpawnHalf = false;

	double timer = 0.0;

	float zombieTimer;
	float witchTimer;
	float warriorTimer;
	float ladyskeletonTimer;
	float ironmanTimer;
	float frankensteinTimer;


	unordered_map<Enemy_Type, vector<Character*>> enemies;
	vector<Character*>* unit;
	Enemy_Castle* castle;
};