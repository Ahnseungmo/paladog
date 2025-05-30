#include "Framework.h"

Paladog::Paladog()
{
    paladogTexture = new Quad(L"Resources/Textures/Paladog/TestPlayer.png");
    paladogTexture->SetParent(this);
    auraTexture = new Quad(L"Resources/Textures/Paladog/Aura.png");
    auraTexture->SetParent(this);
    auraCollider = new RectCollider(Vector2(213, 58));
    auraCollider->SetParent(auraTexture);
}

Paladog::~Paladog()
{
	delete paladogTexture;
    delete auraTexture;
    delete auraCollider;
}

void Paladog::Update()
{
    if (Input::Get()->IsKeyPress('A'))
        Translate(Vector2::Left() * SPEED * DELTA);
    if (Input::Get()->IsKeyPress('D'))
        Translate(Vector2::Right() * SPEED * DELTA);
    auraCollider->UpdateWorld();
    auraTexture->UpdateWorld();
    paladogTexture->UpdateWorld();
	UpdateWorld();
}

void Paladog::Render()
{
    paladogTexture->Render();
    Collider::Render();
    auraCollider->Render();
}

void Paladog::AuraRender()
{
    auraTexture->Render();
}
