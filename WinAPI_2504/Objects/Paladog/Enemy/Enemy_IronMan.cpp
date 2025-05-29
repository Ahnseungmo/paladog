#include "Framework.h"

Enemy_IronMan::Enemy_IronMan()
{
	UnitStat stat;
	stat.maxHp = 300;
	stat.attack = 10;
	stat.moveSpeed = 80;
	stat.attackSpeed = 1.0f;
	stat.attackRange = 70;
	stat.attackCount = 1;

	SetStat(stat);
	SetTeam(TeamType::Enemy);
	CreateClips();
}

Enemy_IronMan::~Enemy_IronMan()
{
}

void Enemy_IronMan::CreateClips()
{
	float setY = Size().y * 0.5f - 30;
	Vector2 thisPos = GetLocalPosition();

	LoadClip("Resources/Textures/Enemy/", "IronMan_Walk.xml", true);
	LoadClip("Resources/Textures/Enemy/", "IronMan_Attack.xml", true);
	LoadClip("Resources/Textures/Enemy/", "IronMan_Dead.xml", false);

	clipTransform->SetLocalPosition({ thisPos.x,thisPos.y + setY });
}
