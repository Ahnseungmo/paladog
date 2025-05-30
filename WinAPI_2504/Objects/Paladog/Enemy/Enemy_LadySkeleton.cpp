#include "Framework.h"

Enemy_LadySkeleton::Enemy_LadySkeleton()
{
	UnitStat stat;
	stat.maxHp = 80;
	stat.attack = 40;
	stat.moveSpeed = 90;
	stat.attackSpeed = 1.2f;
	stat.attackRange = 200;
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

	animation->LoadClip("Resources/Textures/Enemy/", "LadySkeleton_Walk.xml", true);
	animation->LoadClip("Resources/Textures/Enemy/", "LadySkeleton_Attack.xml", true);
	animation->LoadClip("Resources/Textures/Enemy/", "LadySkeleton_Dead.xml", false);

	animation->GetClip(Attack)->SetFrameEvent(8, bind(&Character::AttackTarget, this));

	clipTransform->SetLocalPosition({ thisPos.x,thisPos.y + setY });
	clipTransform->SetLocalScale({ 1.9, 1.9 });
}
