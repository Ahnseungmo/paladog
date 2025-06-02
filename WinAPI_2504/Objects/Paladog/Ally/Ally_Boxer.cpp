#include "Framework.h"

Ally_Boxer::Ally_Boxer() : Character(Vector2(150,150))
{
    MappingAllyData((int)ALLY_TYPE::Boxer);
    SetBaseStat(stat);
    SetTeam(TeamType::Ally);
    CreateClips();
    hpBar->SetBarColor(0, 1, 0);
}

Ally_Boxer::~Ally_Boxer()
{
}

void Ally_Boxer::CreateClips()
{
    Vector2 pos = GetLocalPosition();

    animation->LoadClip("Resources/Textures/Ally_Boxer/", "Ally_Boxer_Walk.xml", true);
    animation->LoadClip("Resources/Textures/Ally_Boxer/", "Ally_Boxer_Attack1.xml", "Ally_Boxer_Attack2.xml", true, stat.attackSpeed);
    animation->LoadClip("Resources/Textures/Ally_Boxer/", "Ally_Boxer_Dead.xml", false);

    animation->GetClip(Attack)->SetFrameEvent(8, bind(&Character::AttackTarget, this));
    animation->GetClip(Attack)->SetFrameEvent(14, bind(&Character::AttackTarget, this));
    animation->GetClip(Attack)->SetFrameEvent(18, bind(&Character::AttackTarget, this));
    animation->GetClip(Attack)->SetFrameEvent(22, bind(&Character::AttackTarget, this));

    clipTransform->SetLocalPosition({ pos.x,pos.y + 90.0f });
}
