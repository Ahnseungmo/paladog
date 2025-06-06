#pragma once

class GameEndingScene : public Scene
{
public :
	GameEndingScene(wstring filePath);
	~GameEndingScene();

	
private:
	Quad* backGround;

	// Scene을(를) 통해 상속됨
	void Update() override;
	void Render() override;

	void ReStart();
private:
	Button* button;
};