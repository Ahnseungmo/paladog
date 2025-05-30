#include "Framework.h"

Ally_Tanker::Ally_Tanker()
{
	UnitStat stat;
	stat.maxHp = 200;
	stat.attack = 0;
	stat.moveSpeed = 140;
	stat.attackSpeed = 1.2f;
	stat.attackRange = 10;
	stat.attackCount = 1;
	SetStat(stat);
	SetTeam(TeamType::Ally);
	CreateClips();
}

Ally_Tanker::~Ally_Tanker()
{

}

void Ally_Tanker::CreateClips()
{
	animation->LoadClip("Resources/Textures/Ally_Tanker/", "Ally_Tanker_Walk.xml", true);
	animation->LoadClip("Resources/Textures/Ally_Tanker/", "Ally_Tanker_Attack.xml", true);
	animation->LoadClip("Resources/Textures/Ally_Tanker/", "Ally_Tanker_Dead.xml", false);
}
