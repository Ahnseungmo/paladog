#pragma once

class CoolTimeButton : public Button 
{
public:
	CoolTimeButton(wstring imagePath, Vector2 size, Vector2 pos, float maxCoolTime);
	~CoolTimeButton();

	void Update();
	void Render();
	void GUIRender();

	void UpdateCoolTime(float cur, float max);

private:
	float maxCoolTime = 0.0f;

	FloatValueBuffer* valueBuffer;
	vector<int>& deck = DataManager::Get()->GetDeck();
};
