#include "Framework.h"

Enemy_Witch::Enemy_Witch()
{
	UnitStat stat;
	stat.maxHp = 100;
	stat.attack = 50;
	stat.moveSpeed = 90;
	stat.attackSpeed = 1.5f;
	stat.attackRange = 300;
	stat.attackCount = 1;

	SetStat(stat);
	SetTeam(TeamType::Enemy);
	CreateClips();
}

Enemy_Witch::~Enemy_Witch()
{
}

void Enemy_Witch::CreateClips()
{
	float setY = Size().y * 0.5f;
	Vector2 thisPos = GetLocalPosition();

	animation->LoadClip("Resources/Textures/Enemy/", "Witch_Walk.xml", true);
	animation->LoadClip("Resources/Textures/Enemy/", "Witch_Attack.xml", true);
	animation->LoadClip("Resources/Textures/Enemy/", "Witch_Dead.xml", false);

	animation->GetClip(Attack)->SetFrameEvent(8, bind(&Character::AttackTarget, this));

	clipTransform->SetLocalPosition({ thisPos.x,thisPos.y + setY });
	clipTransform->SetLocalScale({ 1.9, 1.9 });
}
