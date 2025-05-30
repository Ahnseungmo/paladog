#pragma once

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
	//vector<Character*> GetTargetEnemy();
	vector<Character*>* GetAllUnits();

	void SpawnEnemy(string key);

private:
	template<typename T>
	void CreateEnemy(string key)
	{
		for (int i = 0; i < ENEMY_POOL_SIZE; i++)
		{
			T* enemy = new T;
			enemy->SetActive(false);
			enemies[key].push_back(enemy);
		}
	}


private:
	Vector2 RendomPos();


private:
	unordered_map<string, vector<Character*>> enemies;
};