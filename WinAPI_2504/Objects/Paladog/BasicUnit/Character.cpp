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
    hpBar->Update(GetGlobalPosition(), Size().y, hp, stat.maxHp);
    UpdateWorld();
}

void Character::Render()
{
    Collider::Render();

    worldBuffer->Set(clipTransform->GetWorld());
    worldBuffer->SetVS(0);

    if (curState == Stun)
        animation->Render(Attack);
    else
        animation->Render(curState);
    hpBar->Render();
}

void Character::Edit()
{
    clipTransform->Edit();
    Transform::Edit();
}

void Character::AttackSpeedBuff(float percent)
{
    if (Clip* clip = animation->GetClip(Attack)) {
        if (!isAttackSpeedBuff) {
            stat.attackSpeed *= percent;
            clip->SetSpeed(stat.attackSpeed);
            isAttackSpeedBuff = true;
        }
    }
}

void Character::ResetAttackSpeedBuff(float percent)
{
    if (Clip* clip = animation->GetClip(Attack)) {
        if (isAttackSpeedBuff) {
            stat.attackSpeed /= percent;
            clip->SetSpeed(stat.attackSpeed);
            isAttackSpeedBuff = false;
        }
    }
}

void Character::ResetSpeedBuff(float percent)
{
    if (isSpeedBuff)
    {
        stat.moveSpeed /= percent;
        isSpeedBuff = false;
    }
}

void Character::SpeedBuff(float percent)
{
    if (!isSpeedBuff)
    {
        stat.moveSpeed *= percent;
        isSpeedBuff = true;
    }
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
    if (curState == Stun)
        return;

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

    for (int i = 0; i < targetList->size(); i++)
    {
        Character* unit = (*targetList)[i];
        if (!unit->IsActive() || unit->GetHP() <= 0)
            continue;

        float distanceX = abs(GetGlobalPosition().x - unit->GetGlobalPosition().x);
        float combinedHalfWidth = (Size().x + unit->Size().x) * 0.5f;

        if (distanceX - combinedHalfWidth <= stat.attackRange)
        {
            target = unit;
            break;
        }
    }
}

vector<Character*> Character::FindTargetRange(int maxCount)
{
    vector<Character*> targets;

    if (!targetList)
        return targets;

    for (int i = 0; i < targetList->size(); i++)
    {
        Character* unit = (*targetList)[i];
        if (!unit->IsActive() || unit->GetHP() <= 0)
            continue;

        float distanceX = abs(GetGlobalPosition().x - unit->GetGlobalPosition().x);
        float combinedHalfWidth = (Size().x + unit->Size().x) * 0.5f;

        if (distanceX - combinedHalfWidth <= stat.attackRange)
        {
            targets.push_back(unit);
            if ((int)targets.size() >= maxCount)
                break;
        }
    }

    return targets;
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

void Character::TargetToRun()
{
    if (!targetList)
        return;

    for (Character* unit : *targetList)
    {
        if (!unit->IsActive() || unit->GetHP() <= 0)
            continue;

        unit->SetCurStateToRun();
    }
}

void Character::TargetToStun()
{
    if (!targetList)
        return;

    for (Character* unit : *targetList)
    {
        if (!unit->IsActive() || unit->GetHP() <= 0)
            continue;

        unit->SetCurStateToStun();
    }
}

void Character::MappingCharacterData(int key)
{
    CharacterData data = DataManager::Get()->GetCharacter(key);

    stat.maxHp = data.baseHp;
    stat.attack = data.baseAttack;
    stat.moveSpeed = data.baseSpeed;
    stat.attackSpeed = data.baseAttackSpeed;
    stat.attackRange = data.sightRange;
    stat.attackCount = data.attackCount;

    this->baseStat = stat;
}

void Character::MappingAllyData(int key)
{
    MappingCharacterData(key);
    AllyData data = DataManager::Get()->GetAlly(key);
    int level = 1;
    if (DataManager::Get()->GetBag(key).level) {
        level = DataManager::Get()->GetBag(key).level;
    }
    stat.maxHp += data.hpPerLevel * level;
    stat.attack += data.attackPerLevel * level;
    stat.moveSpeed += data.speedPerLevel * level;
    stat.attackSpeed += data.attackSpeedPerLevel * level;

    //this->baseStat = stat; 
}
