#include "Framework.h"

Ally_Lancer::Ally_Lancer()
{
	UnitStat stat;
	stat.maxHp = 80;
	stat.attack = 20;
	stat.moveSpeed = 110;
	stat.attackSpeed = 1.2f;
	stat.attackRange = 100;
	stat.attackCount = 1;
	SetStat(stat);
	SetTeam(TeamType::Ally);
	CreateClips();
}

Ally_Lancer::~Ally_Lancer()
{
}

void Ally_Lancer::CreateClips()
{
	animation->LoadClip("Resources/Textures/Ally_Lancer/", "Ally_Lancer_Walk.xml", true);
	animation->LoadClip("Resources/Textures/Ally_Lancer/", "Ally_Lancer_Attack1.xml", "Ally_Lancer_Attack2.xml", true,1.0f);
	animation->LoadClip("Resources/Textures/Ally_Lancer/", "Ally_Lancer_Dead.xml", false);
}
