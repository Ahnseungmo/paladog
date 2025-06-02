#pragma once

class IntroScene : public Scene
{
public:
	IntroScene();
	~IntroScene();

	void Update() override;
	void Render() override;
	void GUIRender() override;

	void Start();

	//	bool AnyKeyDown();

private:
	Quad* backGround;

	bool isBooting = false;
	float bootTimer;
	const float BOOT_TIME = 0.1f;
	unordered_map<string, Button*> buttons;

};