#pragma once

class GotchaScene : public Scene
{
public:
	GotchaScene();
	~GotchaScene();

	void Update() override;
	void Render() override;
	void GUIRender() override;

	void Lobby();

	void Gotcha();



	//	bool AnyKeyDown();

private:
	Quad* backGround;
	unordered_map<string, Button*> buttons;
	Chest* chest;

//	Character* pickCharcter;


};