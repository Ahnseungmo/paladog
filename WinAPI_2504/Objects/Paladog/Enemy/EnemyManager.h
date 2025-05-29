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
	vector<Character*> GetTargetEnemy();

	void CreateZombie();
	void CreateWitch();
	void CreateLadySkeleton();
	void CreateFrankenstein();

private:
	Vector2 RendomPos();


private:
	unordered_map<string, vector<EnemyUnit*>> enemies;
};