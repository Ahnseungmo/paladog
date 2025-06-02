#include "Framework.h"

Enemy_Zombie::Enemy_Zombie():Character()
{
	MappingCharacterData(2007);
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

	animation->LoadClip("Resources/Textures/Enemy/", "Zombie_Walk.xml", true);
	animation->LoadClip("Resources/Textures/Enemy/", "Zombie_Attack.xml", true);
	animation->LoadClip("Resources/Textures/Enemy/", "Zombie_Dead.xml", false);

	animation->GetClip(Attack)->SetFrameEvent(8, bind(&Character::AttackTarget, this));

	clipTransform->SetLocalPosition({ thisPos.x,thisPos.y + setY });
	clipTransform->SetLocalScale({ 1.9, 1.9 });
}
