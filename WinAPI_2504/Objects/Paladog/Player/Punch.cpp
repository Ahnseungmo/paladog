#include "Framework.h"

Punch::Punch(Vector2 size) : RectCollider(size)
{
	punchTexture = new Quad(L"Resources/Textures/Paladog/Punch.png");
	punchTexture->SetParent(this);
}

Punch::~Punch()
{
	delete punchTexture;
}

void Punch::Update()
{
	if (!isActive) return;

	Translate(Vector2::Right() * SPEED * DELTA);
	punchTexture->UpdateWorld();
	UpdateWorld();
}

void Punch::Render()
{
	if (!isActive) return;

	punchTexture->Render();
	Collider::Render();
}
