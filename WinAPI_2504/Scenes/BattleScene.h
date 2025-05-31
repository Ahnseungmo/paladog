#pragma once

class BattleScene : public Scene
{
private:
	const float LEFT_EDGE = -500.0f;
	const float RIGHT_EDGE = 1280.0f;
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
	Background* background = nullptr;
};
