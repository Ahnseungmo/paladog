#pragma once

class BattleScene : public Scene
{
public:
	BattleScene();
	~BattleScene();

	void Update() override;
	void Render() override;

private:
	Ally_Knight* allyK = nullptr;
	Ally_Lancer* allyL = nullptr;
	Ally_Tanker* allyT = nullptr;
	Ally_Archer* allyA = nullptr;
	Ally_Elite* allyE = nullptr;
	Ally_Boxer* allyB = nullptr;

	EnemyUnit* enemy = nullptr;
	EnemyUnit* enemy1 = nullptr;

	vector<Character*> allies;
	vector<Character*> enemies;
};
