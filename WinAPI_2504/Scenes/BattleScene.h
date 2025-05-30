#pragma once

class BattleScene : public Scene
{
public:
	BattleScene();
	~BattleScene();

	void Update() override;
	void Render() override;

	/*void PostRender() override;

	void Start() override;
	void End() override;*/

private:
	Ally_Knight* allyK = nullptr;
	Ally_Lancer* allyL = nullptr;
	Ally_Tanker* allyT = nullptr;
	Ally_Archer* allyA = nullptr;
	Ally_Elite* allyE = nullptr;
	Ally_Boxer* allyB = nullptr;

	Enemy_Witch* enemy = nullptr;

	Enemy_Castle* castle = nullptr;

	vector<Character*> allies;
	vector<Character*> enemies;

	Panel* playerPanel = nullptr;
	Paladog* paladog = nullptr;
};
