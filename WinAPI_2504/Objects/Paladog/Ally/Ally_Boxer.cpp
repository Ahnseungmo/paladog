#include "Framework.h"

Ally_Boxer::Ally_Boxer()
{
    UnitStat stat;
    stat.maxHp = 200;
    stat.attack = 30;
    stat.moveSpeed = 140;
    stat.attackSpeed = 1.0f;
    stat.attackRange = 150;
    stat.attackCount = 1;
    SetStat(stat);
    SetTeam(TeamType::Ally);
    CreateClips();
}

Ally_Boxer::~Ally_Boxer()
{
}

void Ally_Boxer::CreateClips()
{
    LoadClip("Resources/Textures/Ally_Boxer/", "Ally_Boxer_Walk.xml", true);
    LoadClip("Resources/Textures/Ally_Boxer/", "Ally_Boxer_Attack1.xml", "Ally_Boxer_Attack2.xml", true, 1.0f);
    LoadClip("Resources/Textures/Ally_Boxer/", "Ally_Boxer_Dead.xml", false);
}
