#pragma once

class UnitDataPanel : public Transform
{
public:
	UnitDataPanel(Vector2 pos);
	~UnitDataPanel();

	void Update();
	void Render();

	void CreateUnitData();
	void CreateUnitStatusBar();
	void DisplayUnit(void* keydata);
//	void CreateButtons();

private:
	//    Quad* panelTexture;
	const int UNITCOUNT = 10;
	const float BUTTON_WIDTH = 120.0f;
	const float BUTTON_HEIGHT = 120.0f;
	const float BUTTON_SPACING = 5.0f;
	const float BAR_WIDTH = 293.0f;

	float startX;

	vector<Button*> buttons;
	unordered_map<int,Quad*> unitTexture;
	vector<Quad*> unitStatusBar;
	float UnitStatusBarPadding = 75.0f;

	unordered_map<int, wstring> unitImages = {
		{1001, L"Resources/Textures/Paladog/Unit/Units/Knight.png"},
		{1002, L"Resources/Textures/Paladog/Unit/Units/Archer.png"},
		{1003, L"Resources/Textures/Paladog/Unit/Units/Boxer.png"},
		{1004, L"Resources/Textures/Paladog/Unit/Units/Lancer.png"},
		{1005, L"Resources/Textures/Paladog/Unit/Units/Tanker.png"},
		{1006, L"Resources/Textures/Paladog/Unit/Units/Elite.png"},
		{1007, L"Resources/Textures/Paladog/Unit/Units/Bomber.png"}
	};
	

};

