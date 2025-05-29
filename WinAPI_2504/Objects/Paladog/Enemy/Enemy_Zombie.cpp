#include "Framework.h"

Enemy_Zombie::Enemy_Zombie():Character()
{
	UnitStat stat;
	stat.maxHp = 130;
	stat.attack = 15;
	stat.moveSpeed = 90;
	stat.attackSpeed = 1.2f;
	stat.attackRange = 70;
	stat.attackCount = 1;

	SetStat(stat);
	SetTeam(TeamType::Enemy);
	CreateClips();
}

Enemy_Zombie::~Enemy_Zombie()
{
}

void Enemy_Zombie::CreateClips()
{
	float setY = Size().y * 0.5f;
	Vector2 thisPos = GetLocalPosition();

	LoadClip("Resources/Textures/Enemy/", "Zombie_Walk.xml", true);
	LoadClip("Resources/Textures/Enemy/", "Zombie_Attack.xml", true);
	LoadClip("Resources/Textures/Enemy/", "Zombie_Dead.xml", false);

	clipTransform->SetLocalPosition({ thisPos.x,thisPos.y + setY });
}
