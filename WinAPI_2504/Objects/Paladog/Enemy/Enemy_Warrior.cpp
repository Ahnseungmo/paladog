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

	animation->LoadClip("Resources/Textures/Enemy/", "Warrior_Walk.xml", true);
	animation->LoadClip("Resources/Textures/Enemy/", "Warrior_Attack.xml", true);
	animation->LoadClip("Resources/Textures/Enemy/", "Warrior_Dead.xml", false);

	animation->GetClip(Attack)->SetFrameEvent(5, bind(&Character::AttackTarget, this));

	clipTransform->SetLocalPosition({ thisPos.x,thisPos.y + setY });
	clipTransform->SetLocalScale({ 1.9, 1.9 });
}
