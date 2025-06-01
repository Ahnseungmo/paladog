#include "Framework.h"

Bomb::Bomb(Vector2 size) : RectCollider(size)
{
    clipTransform = new Transform();
    clipTransform->SetParent(this);

    animation = new CharacterAnimation();
    worldBuffer = new MatrixBuffer();

    animation->LoadClip("Resources/Textures/Ally_Bomber/", "Boom1.xml", "Boom2.xml", true,2.0f);
    animation->LoadClip("Resources/Textures/Ally_Bomber/", "BoomEffect.xml", false);
}

Bomb::~Bomb()
{
    delete clipTransform;
    delete animation;
    delete worldBuffer;
}

void Bomb::Fire(Vector2 pos, vector<Character*> targets)
{
    SetLocalPosition(pos);
    this->targets = targets;

    if (!targets.empty())
    {
        dir = targets[0]->GetGlobalPosition() - pos;
        dir.Normalize();
    }
    else
    {
        dir = Vector2::Right(); 
    }

    state = BombState::Flying;
    SetActive(true);
    animation->Play(0); 
}

void Bomb::Update()
{
    if (!IsActive() || targets.empty() || targets[0] == nullptr || !targets[0]->IsActive())
    {
        SetActive(false);
        return;
    }

    switch (state)
    {
    case BombState::Flying:
        Move();
        animation->Update(0);
        if (!targets.empty())
        {
            float dist = (GetGlobalPosition() - targets[0]->GetGlobalPosition()).Magnitude();
            if (dist < 10.0f)
            {
                Explode();
            }
        }
        break;

    case BombState::Exploding:
        animation->Update(1);
        if (!animation->IsPlay(1))
            SetActive(false);
        break;
    }

    clipTransform->UpdateWorld();
    UpdateWorld();
}

void Bomb::Move()
{
    Vector2 dirVec = targets[0]->GetGlobalPosition() - GetGlobalPosition();
    dir = dirVec.GetNormalized();

    float angle = atan2(dir.y, dir.x);
    SetRotationZ(angle);

    Translate(dir * speed * DELTA);
}

void Bomb::Explode()
{
    for (int i = 0; i < targets.size(); i++)
    {
        if (targets[i]->IsActive())
        {
            targets[i]->TakeDamage(20);
        }
    }

    animation->Play(1); 
    state = BombState::Exploding;
}

void Bomb::Render()
{
    if (!IsActive()) return;

    worldBuffer->Set(clipTransform->GetWorld());
    worldBuffer->SetVS(0);

    if (state == BombState::Flying)
        animation->Render(0);
    else
        animation->Render(1);

    Collider::Render();
}
