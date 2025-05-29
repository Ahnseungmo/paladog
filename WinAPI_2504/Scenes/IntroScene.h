#pragma once

class IntroScene : public Scene
{
public:
	IntroScene();
	~IntroScene();

	void Update() override;
	void Render() override;
	void GUIRender() override;

	bool AnyKeyDown();

private:
	Quad* backGround;
	bool isBooting = false;
	float bootTimer;
	const float BOOT_TIME = 0.3f;
};