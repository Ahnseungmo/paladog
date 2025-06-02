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

	void RefreshMoney();



	//	bool AnyKeyDown();

private:
	Quad* backGround;
	unordered_map<string, Button*> buttons;
	Chest* chest;
	unordered_map<int,Quad*> characterQuads;
	TextBox* haveCoin;
	Quad* haveCoinBack;

	TextBox* gotchaCost;

	int pickCharcterIndex = 0;

//	Character* pickCharcter;


};