#pragma once

class GameEndingScene : public Scene
{
public :
	GameEndingScene(wstring filePath);
	~GameEndingScene();

	
private:
	Quad* backGround;

	// Scene��(��) ���� ��ӵ�
	void Update() override;
	void Render() override;

	void ReStart();
private:
	Button* button;
};