#pragma once

class LobbyScene : public Scene
{
public:
	LobbyScene();
	~LobbyScene();

	void Update() override;
	void Render() override;
	void GUIRender() override;

	void StartGame();


private:
	Quad* backGround;
	unordered_map<string,Button*> buttons;

};