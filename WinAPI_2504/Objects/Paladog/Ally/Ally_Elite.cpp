#include "Framework.h"

Ally_Elite::Ally_Elite()
{
	UnitStat stat;
	stat.maxHp = 280;
	stat.attack = 80;
	stat.moveSpeed = 130;
	stat.attackSpeed = 1.2f;
	stat.attackRange = 60;
	stat.attackCount = 1;
	SetStat(stat);
	SetTeam(TeamType::Ally);
	CreateClips();
}

Ally_Elite::~Ally_Elite()
{
}

void Ally_Elite::CreateClips()
{
	animation->LoadClip("Resources/Textures/Ally_Elite/", "Ally_Elite_Walk.xml", true);
	animation->LoadClip("Resources/Textures/Ally_Elite/", "Ally_Elite_Attack1.xml", "Ally_Elite_Attack2.xml", true, 1.0f);
	animation->LoadClip("Resources/Textures/Ally_Elite/", "Ally_Elite_Dead.xml", false);
}
