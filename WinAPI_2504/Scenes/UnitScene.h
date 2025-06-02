#pragma once

class UnitScene : public Scene
{
public:
	UnitScene();
	~UnitScene();

	void Start();

	void End();

	void Update() override;
	void Render() override;
	void GUIRender() override;

	void Lobby();
	UnitDataPanel* GetUnitDataPanel() { return unitDataPanel; }
	void DisplayUnit(int key);

private:
	Quad* backGround;
	unordered_map<string, Button*> buttons;
	const float BUTTON_PADDING = 100;
	UnitPanel* unitPanel;
	UnitDataPanel* unitDataPanel;
};