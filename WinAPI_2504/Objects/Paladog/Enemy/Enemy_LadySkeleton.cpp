#include "Framework.h"

Enemy_LadySkeleton::Enemy_LadySkeleton()
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

Enemy_LadySkeleton::~Enemy_LadySkeleton()
{
}

void Enemy_LadySkeleton::CreateClips()
{
	float setY = Size().y * 0.5f;
	Vector2 thisPos = GetLocalPosition();

	LoadClip("Resources/Textures/Enemy/", "LadySkeleton_Walk.xml", true);
	LoadClip("Resources/Textures/Enemy/", "LadySkeleton_Attack.xml", true);
	LoadClip("Resources/Textures/Enemy/", "LadySkeleton_Dead.xml", false);

	clipTransform->SetLocalPosition({ thisPos.x,thisPos.y + setY });
}
