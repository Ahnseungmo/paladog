#include "Framework.h"

Allow::Allow(Vector2 size)
{
    clipTransform = new Transform();
    clipTransform->SetParent(this);
    clipTransform->SetTag("Allow");

    worldBuffer = new MatrixBuffer();

    animation = new CharacterAnimation();
}

Allow::~Allow()
{
    delete animation;
    delete clipTransform;
    delete worldBuffer;
}

void Allow::Update()
{
    clipTransform->UpdateWorld();
    UpdateWorld();
}

void Allow::Render()
{
    Collider::Render();

    worldBuffer->Set(clipTransform->GetWorld());
    worldBuffer->SetVS(0);
    animation->Render(0);
}

void Allow::Move(Vector2 pos)
{
    Translate(pos * 300.0f * DELTA);
}
