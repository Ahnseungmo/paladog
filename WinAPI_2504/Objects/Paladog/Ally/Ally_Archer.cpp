#include "Framework.h"

Ally_Archer::Ally_Archer()
{
    UnitStat stat;
    stat.maxHp = 40;
    stat.attack = 40;
    stat.moveSpeed = 120;
    stat.attackSpeed = 1.0f;
    stat.attackRange = 150;
    stat.attackCount = 1;
    SetStat(stat);
    SetTeam(TeamType::Ally);
    CreateClips();
}

Ally_Archer::~Ally_Archer()
{
}

void Ally_Archer::CreateClips()
{
    LoadClip("Resources/Textures/Ally_Archer/", "Ally_Archer_Walk.xml", true);
    LoadClip("Resources/Textures/Ally_Archer/", "Ally_Archer_Attack.xml", true);
    LoadClip("Resources/Textures/Ally_Archer/", "Ally_Archer_Dead.xml", false);
}





