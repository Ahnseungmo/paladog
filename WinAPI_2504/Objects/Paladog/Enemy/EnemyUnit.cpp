#include "Framework.h"

EnemyUnit::EnemyUnit()
{
	UnitStat stat;
	stat.maxHp = 80;
	stat.attack = 15;
	stat.moveSpeed = 90;
	stat.attackSpeed = 1.2f;
	stat.attackRange = 70;
	stat.attackCount = 1;

	SetStat(stat);
	SetTeam(TeamType::Enemy);
	CreateClips();
}

EnemyUnit::~EnemyUnit()
{
}

void EnemyUnit::CreateClips()
{
	LoadClip("Resources/Textures/Ally_Knight/", "Ally_Knight_Walk.xml", true);
	LoadClip("Resources/Textures/Ally_Knight/", "Ally_Knight_Attack.xml", true);
	LoadClip("Resources/Textures/Ally_Knight/", "Ally_Knight_Dead.xml", false);
}

