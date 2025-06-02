#pragma once

class UpgradeScene : public Scene
{
public:
	UpgradeScene();
	~UpgradeScene();

	void Update() override;
	void Render() override;
	void GUIRender() override;

	void Lobby();


private:
	Quad* backGround;
	unordered_map<string, Button*> buttons;
	const float BUTTON_PADDING = 100;

};