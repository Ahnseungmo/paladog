#include "Framework.h"

Allow::Allow(Vector2 size) : RectCollider(size)
{
    clipTransform = new Transform();
    clipTransform->SetParent(this);

    worldBuffer = new MatrixBuffer();
    animation = new CharacterAnimation();

    animation->LoadClip("Resources/Textures/Ally_Archer/", "Allow.xml", false);
}

Allow::~Allow()
{
    delete clipTransform;
    delete animation;
    delete worldBuffer;
}

void Allow::Update()
{
    if (!IsActive() || target == nullptr || !target->IsActive())
    {
        SetActive(false);
        return;
    }

    Move();
    animation->Update(0);
    clipTransform->UpdateWorld();
    UpdateWorld();
}

void Allow::Render()
{
    if (!IsActive()) return;

    worldBuffer->Set(clipTransform->GetWorld());
    worldBuffer->SetVS(0);
    animation->Render(0);

    Collider::Render();
}

void Allow::Fire(Vector2 startPos, Character* target)
{
    SetLocalPosition(startPos);
    this->target = target;

    if (target != nullptr)
    {
        Vector2 dirVec = target->GetGlobalPosition() - startPos;
        dir = dirVec.GetNormalized();
    }
    else
    {
        dir = Vector2::Right();
    }

    SetActive(true);
}

void Allow::Move()
{
    Vector2 dirVec = target->GetGlobalPosition() - GetGlobalPosition();
    dir = dirVec.GetNormalized();

    float angle = atan2(dir.y, dir.x);
    SetRotationZ(angle);

    Translate(dir * speed * DELTA);

    float distance = (GetGlobalPosition() - target->GetGlobalPosition()).Magnitude();
    if (distance < 10.0f)
    {
        target->TakeDamage(10);
        SetActive(false);
    }
}
