#pragma once

class LobbyScene : public Scene
{
public:
	LobbyScene();
	~LobbyScene();

	void Update() override;
	void Render() override;
	void GUIRender() override;

	void Battle();

	void Gotcha();


	void Unit();

	void Hero();


private:
	Quad* backGround;
	unordered_map<string, Button*> buttons;
	const float BUTTON_PADDING = 100;

};