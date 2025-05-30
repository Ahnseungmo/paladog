#include "Framework.h"

Ally_Archer::Ally_Archer() : Character(Vector2(140, 140))
{
    UnitStat stat;
    stat.maxHp = 240;
    stat.attack = 10;
    stat.moveSpeed = 120;
    stat.attackSpeed = 1.0f;
    stat.attackRange = 300;
    stat.attackCount = 1;
    SetBaseStat(stat);
    SetTeam(TeamType::Ally);
    CreateClips();
    hpBar->SetBarColor(0, 1, 0);
}

Ally_Archer::~Ally_Archer()
{
}

void Ally_Archer::CreateClips()
{
    Vector2 pos = GetLocalPosition();

    animation->LoadClip("Resources/Textures/Ally_Archer/", "Ally_Archer_Walk.xml", true);
    animation->LoadClip("Resources/Textures/Ally_Archer/", "Ally_Archer_Attack.xml", true);
    animation->LoadClip("Resources/Textures/Ally_Archer/", "Ally_Archer_Dead.xml", false);

    animation->GetClip(Attack)->SetFrameEvent(9, bind(&Character::AttackTarget, this));
    animation->GetClip(Attack)->SetFrameEvent(13, bind(&Character::AttackTarget, this));
    animation->GetClip(Attack)->SetFrameEvent(16, bind(&Character::AttackTarget, this));
    animation->GetClip(Attack)->SetFrameEvent(19, bind(&Character::AttackTarget, this));

    clipTransform->SetLocalPosition({ pos.x,pos.y + 90.0f });
}





