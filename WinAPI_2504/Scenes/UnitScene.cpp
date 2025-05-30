#include "Framework.h"
#include "UnitScene.h"

UnitScene::UnitScene()
{
	backGround = new Quad(L"Resources/Textures/Paladog/Unit/unit_back.png", Vector2(0, 0), Vector2(1.0f, 1.0f));
	backGround->SetLocalPosition(CENTER);
	backGround->UpdateWorld();
}

UnitScene::~UnitScene()
{
	delete backGround;
}

void UnitScene::Update()
{

}

void UnitScene::Render()
{
	backGround->Render();
}

void UnitScene::GUIRender()
{
}
