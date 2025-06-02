#pragma once

class SpawnBar : public Transform 
{
private:
	const float SPEED = 50.0f;
	const float SPAWNBAR_WIDTH = 370.0f;
	const float SPAWNBAR_HEIGHT = 33.0f;
	const float SPAWNBAR_POSX = 273.0f;
	const float SPAWNBAR_POSY = 258.0f;

public:
	SpawnBar();
	~SpawnBar();

	void Update();
	void Render();

	float GetMaxSpawn() { return maxSpawnGauge; }
	void SetMaxSpawn(float maxSpawn) { this->maxSpawnGauge = maxSpawn; }	
	float GetCurSpawn() { return curSpawnGauge; }
	void SetCurSpawn(float curSpawn) { this->curSpawnGauge = curSpawn; }

private:
	float maxSpawnGauge = 200.0f;
	float curSpawnGauge = 0.0f;
	float ratio = 0.0f;
	float curSpawnBarWidth = 0.0f;

	Quad* maxSpawnBarTexture;
	Quad* curSpawnBarTexture;

	Vector2 curSpawnBarGauge = Vector2(0, 0);
};
