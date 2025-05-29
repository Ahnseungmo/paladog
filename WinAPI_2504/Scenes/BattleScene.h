#pragma once

class BattleScene : public Scene
{
public:
	BattleScene();
	~BattleScene();

	void Update() override;
	void Render() override;

private:
	Ally_Knight* ally = nullptr;
	EnemyUnit* enemy = nullptr;

	Ally_Knight* ally1 = nullptr;
	EnemyUnit* enemy1 = nullptr;

	vector<Character*> allies;
	vector<Character*> enemies;
};
