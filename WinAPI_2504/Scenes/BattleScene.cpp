#include "Framework.h"
#include "BattleScene.h"

BattleScene::BattleScene()
{
	background = new Background(LEFT_EDGE, RIGHT_EDGE);

	playerPanel = new Panel(Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 240));
	playerPanel->UpdateWorld();

	paladog = new Paladog();
	paladog->SetLocalPosition(CENTER + Vector2(0, 100));
	paladog->UpdateWorld();

	playerPanel->SetPaladog(paladog);

	EnemyManager::Get()->SpawnEnemy(Enemy_Type::Castle);

	AllyManager::Get()->AddPalaDog(paladog);
	AllyManager::Get()->SetTargetList(EnemyManager::Get()->GetAllUnits());
	EnemyManager::Get()->SetTargetList(AllyManager::Get()->GetAllUnits());
}

BattleScene::~BattleScene()
{
	delete background;
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
	background->Render();
	paladog->AuraRender();
	
	ArrayRendering();
}

void BattleScene::PostRender()
{
	if (playerPanel)
		playerPanel->Render();
}

void BattleScene::Start()
{
	playerPanel->Start();
	Environment::Get()->GetMainCamera()->SetTarget(paladog);
	Environment::Get()->GetMainCamera()->SetLimits(LEFT_EDGE, RIGHT_EDGE + 500);
	EnemyManager::Get()->ResetEnemy();
}

void BattleScene::End()
{
	Environment::Get()->GetMainCamera()->SetTarget(nullptr);

}

void BattleScene::ArrayRendering()
{
	vector<Character*> units;
	units.push_back(paladog);

	vector<Character*> allyUnits = AllyManager::Get()->ActiveUnits();
	vector<Character*> enemyUnits = EnemyManager::Get()->ActiveUnits();

	units.insert(units.end(), allyUnits.begin(), allyUnits.end());
	units.insert(units.end(), enemyUnits.begin(), enemyUnits.end());

	sort(units.begin(), units.end(), [](Character* a, Character* b) {
		return a->GetGlobalPosition().y > b->GetGlobalPosition().y;
	});

	for (int i = 0; i < units.size(); i++)
	{
		units[i]->Render();
	}
}
