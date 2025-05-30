#include "Framework.h"

Ally_Bomber::Ally_Bomber()
{
    UnitStat stat;
    stat.maxHp = 240;
    stat.attack = 30;
    stat.moveSpeed = 120;
    stat.attackSpeed = 1.0f;
    stat.attackRange = 300;
    stat.attackCount = 1;
    SetBaseStat(stat);
    SetTeam(TeamType::Ally);
    CreateClips();
    hpBar->SetBarColor(0, 1, 0);
}

Ally_Bomber::~Ally_Bomber()
{
}

void Ally_Bomber::CreateClips()
{
    Vector2 pos = GetLocalPosition();

    animation->LoadClip("Resources/Textures/Ally_Bomber/", "Ally_Bomber_Walk.xml", true);
    animation->LoadClip("Resources/Textures/Ally_Bomber/", "Ally_Bomber_Attack.xml", true);
    animation->LoadClip("Resources/Textures/Ally_Bomber/", "Ally_Bomber_Dead.xml", false);

    animation->GetClip(Attack)->SetFrameEvent(6, bind(&Character::AttackTarget, this));
    
    clipTransform->SetLocalPosition({ pos.x,pos.y + 90.0f });
}
