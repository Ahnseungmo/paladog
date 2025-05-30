#pragma once

class BattleScene : public Scene
{
public:
	BattleScene();
	~BattleScene();

	void Update() override;
	void Render() override;

	void PostRender() override;

	void Start() override;
	void End() override;

private:
	Panel* playerPanel = nullptr;
	Paladog* paladog = nullptr;
};
