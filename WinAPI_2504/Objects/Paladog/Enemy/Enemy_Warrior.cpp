#include "Framework.h"

Enemy_Warrior::Enemy_Warrior()
{
	UnitStat stat;
	stat.maxHp = 80;
	stat.attack = 40;
	stat.moveSpeed = 90;
	stat.attackSpeed = 1.2f;
	stat.attackRange = 150;
	stat.attackCount = 1;

	SetStat(stat);
	SetTeam(TeamType::Enemy);
	CreateClips();
}

Enemy_Warrior::~Enemy_Warrior()
{
}

void Enemy_Warrior::CreateClips()
{
	float setY = Size().y * 0.5f - 30;
	Vector2 thisPos = GetLocalPosition();

	LoadClip("Resources/Textures/Enemy/", "Warrior_Walk.xml", true);
	LoadClip("Resources/Textures/Enemy/", "Warrior_Attack.xml", true);
	LoadClip("Resources/Textures/Enemy/", "Warrior_Dead.xml", false);

	clipTransform->SetLocalPosition({ thisPos.x,thisPos.y + setY });
}
