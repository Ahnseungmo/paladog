#include "Framework.h"
#include "IntroScene.h"

IntroScene::IntroScene()
{
	backGround = new Quad(L"Resources/Textures/Paladog/IntroBackGround.png", Vector2(0, 0), Vector2(1.0f, 1.0f));
	backGround->SetLocalPosition(CENTER);
	backGround->UpdateWorld();
}

IntroScene::~IntroScene()
{
	delete backGround;

}

void IntroScene::Update()
{
	if (!isBooting && bootTimer > BOOT_TIME) isBooting = true;
	else bootTimer += DELTA;
	if (!isBooting) return;


	if (AnyKeyDown()) {
		SceneManager::Get()->ChangeScene("Lobby");

	}
}

void IntroScene::Render()
{
	backGround->Render();
}

void IntroScene::GUIRender()
{
}

bool IntroScene::AnyKeyDown() {
	for (int i = 0; i < Input::Get()->KEY_MAX; i++)
		if (Input::Get()->IsKeyDown(i)) return true;
	return false;
}