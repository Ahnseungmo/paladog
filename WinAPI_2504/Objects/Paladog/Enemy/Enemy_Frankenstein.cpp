#include "Framework.h"

Enemy_Frankenstein::Enemy_Frankenstein():Character(Vector2(70, 100))
{
	UnitStat stat;
	stat.maxHp = 300;
	stat.attack = 60;
	stat.moveSpeed = 80;
	stat.attackSpeed = 1.0f;
	stat.attackRange = 70;
	stat.attackCount = 1;

	SetStat(stat);
	SetTeam(TeamType::Enemy);
	CreateClips();
}

Enemy_Frankenstein::~Enemy_Frankenstein()
{
}

void Enemy_Frankenstein::CreateClips()
{
	float setY = Size().y * 0.5f - 30;
	Vector2 thisPos = GetLocalPosition();

	LoadClip("Resources/Textures/Enemy/", "Frankenstein_Walk.xml", true);
	LoadClip("Resources/Textures/Enemy/", "Frankenstein_Attack.xml", true);
	LoadClip("Resources/Textures/Enemy/", "Frankenstein_Dead.xml", false);

	clipTransform->SetLocalPosition({ thisPos.x,thisPos.y + setY });
}
