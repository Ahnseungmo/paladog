#include "Framework.h"

SpawnBar::SpawnBar()
{
	maxSpawnBarTexture = new Quad(L"Resources/Textures/UI/MaxSpawnBar.png");
	maxSpawnBarTexture->SetParent(this);
	maxSpawnBarTexture->SetLocalPosition(SPAWNBAR_POSX, SPAWNBAR_POSY);
	maxSpawnBarTexture->SetSize(Vector2(SPAWNBAR_WIDTH, SPAWNBAR_HEIGHT));
	maxSpawnBarTexture->UpdateWorld();

	curSpawnBarTexture = new Quad(L"Resources/Textures/UI/CurSpawnBar.png");
	curSpawnBarTexture->SetParent(this);
	curSpawnBarTexture->SetLocalPosition(SPAWNBAR_POSX, SPAWNBAR_POSY);
	curSpawnBarTexture->SetSize(Vector2(SPAWNBAR_WIDTH, SPAWNBAR_HEIGHT));
	curSpawnBarTexture->UpdateWorld();
}

SpawnBar::~SpawnBar()
{
	delete maxSpawnBarTexture;
	delete curSpawnBarTexture;
}

void SpawnBar::Update()
{
	if(curSpawnGauge <= maxSpawnGauge)
		curSpawnGauge += SPEED * DELTA;

	ratio = curSpawnGauge / maxSpawnGauge;
	curSpawnBarWidth = SPAWNBAR_WIDTH * ratio;
	curSpawnBarTexture->SetSize(Vector2(curSpawnBarWidth, SPAWNBAR_HEIGHT));
	float leftEdgeX = SPAWNBAR_POSX - (SPAWNBAR_WIDTH / 2);
    float newPosX = leftEdgeX + (curSpawnBarWidth / 2);
    curSpawnBarTexture->SetLocalPosition(Vector2(newPosX - SPAWNBAR_WIDTH - SPAWNBAR_POSX, SPAWNBAR_HEIGHT * 3));
    curSpawnBarTexture->UpdateWorld();
}

void SpawnBar::Render()
{
	maxSpawnBarTexture->Render();
	curSpawnBarTexture->Render();
}
