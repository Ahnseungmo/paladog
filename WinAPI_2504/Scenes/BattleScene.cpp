#include "Framework.h"
#include "BattleScene.h"

BattleScene::BattleScene()
{
	playerPanel = new Panel(Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 240));
	playerPanel->UpdateWorld();

	playerPanel->CreateButtons();

	paladog = new Paladog();
	paladog->SetLocalPosition(CENTER + Vector2(0, 100));
	paladog->UpdateWorld();



	EnemyManager::Get()->SpawnEnemy("Zombie");
	EnemyManager::Get()->SpawnEnemy("Witch");
	EnemyManager::Get()->SpawnEnemy("Castle");

	AllyManager::Get()->SetTargetList(EnemyManager::Get()->GetAllUnits());
	EnemyManager::Get()->SetTargetList(AllyManager::Get()->GetAllUnits());
}

BattleScene::~BattleScene()
{
	delete playerPanel;
	delete paladog;

	AllyManager::Delete();
	EnemyManager::Delete();
}

void BattleScene::Update()
{
	if (playerPanel)
		playerPanel->Update();
	paladog->Update();

	if (Input::Get()->IsKeyDown('1'))
	{
		AllyManager::Get()->Spawn(ALLY_TYPE::Boxer);
	}

	AllyManager::Get()->Update();
	EnemyManager::Get()->Update();
}

void BattleScene::Render()
{
	paladog->AuraRender();
	paladog->Render();

	AllyManager::Get()->Render();
	EnemyManager::Get()->Render();
}

void BattleScene::PostRender()
{
	if (playerPanel)
		playerPanel->Render();
}

void BattleScene::Start()
{
	Environment::Get()->GetMainCamera()->SetTarget(paladog);
}

void BattleScene::End()
{
	Environment::Get()->GetMainCamera()->SetTarget(nullptr);
}
