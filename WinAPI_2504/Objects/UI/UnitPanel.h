#pragma once

class UnitPanel : public Transform
{
public:
    UnitPanel(Vector2 pos);
    ~UnitPanel();

    void Update();
    void Render();

    void CreateButtons();
//	void SelectUnit();
	void SelectUnit(int key);
	void EquipUnit(int key);
	void CheckEquipUnit(int key, bool check);
//	void SetParent(UnitScene* scene) { parentScene = scene; }

private:
//    Quad* panelTexture;
    const int UNITCOUNT = 10;
    const float BUTTON_WIDTH = 120.0f;
    const float BUTTON_HEIGHT = 120.0f;
	const float BUTTON_SPACING = 5.0f;

	float startX;

    vector<Button*> buttons;
//	Transform* moneyTransform;
	TextBox* textBox;
	unordered_map<int, Quad*> checkUnits;
//	UnitScene* parentScene;

	unordered_map<int, wstring> unitImages = {
		{1001, L"Resources/Textures/Paladog/Unit/Knight.png"},
		{1002, L"Resources/Textures/Paladog/Unit/Archer.png"},
		{1003, L"Resources/Textures/Paladog/Unit/Boxer.png"},
		{1004, L"Resources/Textures/Paladog/Unit/Lancer.png"},
		{1005, L"Resources/Textures/Paladog/Unit/Tanker.png"},
		{1006, L"Resources/Textures/Paladog/Unit/Elite.png"},
		{1007, L"Resources/Textures/Paladog/Unit/Bomber.png"}
	};

};

