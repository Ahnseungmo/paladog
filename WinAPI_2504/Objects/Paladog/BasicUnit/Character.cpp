#include "Framework.h"

Character::Character(Vector2 size) : RectCollider(size)
{
    clipTransform = new Transform();
    clipTransform->SetParent(this);
    clipTransform->SetTag("CharacterClip");

    worldBuffer = new MatrixBuffer();

    animation = new CharacterAnimation();
    hpBar = new HealthBar();
}

Character::~Character()
{
    delete animation;
    delete hpBar;
    delete clipTransform;
    delete worldBuffer;
}

void Character::Update()
{
    if (curState != Dead)
        State();

    Animation();
    clipTransform->UpdateWorld();
    hpBar->Update(GetGlobalPosition(),Size().y, hp, stat.maxHp);
    UpdateWorld();
}

void Character::Render()
{
    Collider::Render();

    worldBuffer->Set(clipTransform->GetWorld());
    worldBuffer->SetVS(0);
    animation->Render(curState);
    hpBar->Render();
}

void Character::Edit()
{
    clipTransform->Edit();
    Transform::Edit();
}

void Character::AttackSpeedBuff()
{
    if (Clip* clip = animation->GetClip(Attack))
        clip->SetSpeed(stat.attackSpeed * attackSpeedBuff);
}

void Character::SpeedBuff()
{
    stat.moveSpeed *= speedBuff;
    if (Clip* clip = animation->GetClip(Run))
        clip->SetSpeed(clip->GetSpeed() * speedBuff);
}

void Character::Move()
{
    if (team == TeamType::Ally)
        Translate(Vector2::Right() * stat.moveSpeed * DELTA);
    else
        Translate(Vector2::Left() * stat.moveSpeed * DELTA);
}

void Character::State()
{
    FindTarget();
    if (target)
        curState = Attack;
    else
        curState = Run;
}

void Character::Animation()
{
    switch (curState)
    {
    case Run:
        Move();
        animation->Update(Run);
        break;
    case Attack:
        animation->Update(Attack);
        break;
    case Dead:
        //SetActive(false);
        animation->Update(Dead);
        if (!animation->IsPlay(Dead))
            SetActive(false);
        break;
    }
}

void Character::FindTarget()
{
    target = nullptr;

    if (!targetList) return;

    for (Character* unit : *targetList)
    {
        if (!unit->IsActive() || unit->GetHP() <= 0 )
            continue;

        float distance = abs(GetGlobalPosition().x - unit->GetGlobalPosition().x);

        if (distance <= stat.attackRange)
        {
            target = unit;
            break;
        }
    }
}

void Character::AttackTarget()
{
    if (target && target->IsActive())
        target->TakeDamage(stat.attack);
}

void Character::TakeDamage(float damage)
{
    if (curState == Dead)
        return;

    hp -= damage;
    if (hp <= 0.0f)
    {
        hp = 0.0f;
        curState = Dead;
        animation->Play(Dead);
    }
}

