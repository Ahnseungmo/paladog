#include "Framework.h"

Enemy_Frankenstein::Enemy_Frankenstein()
{
	MappingCharacterData(2002);
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

	animation->LoadClip("Resources/Textures/Enemy/", "Frankenstein_Walk.xml", true);
	animation->LoadClip("Resources/Textures/Enemy/", "Frankenstein_Attack.xml", true);
	animation->LoadClip("Resources/Textures/Enemy/", "Frankenstein_Dead.xml", false);

	animation->GetClip(Attack)->SetFrameEvent(10, bind(&Character::AttackTarget, this));

	clipTransform->SetLocalPosition({ thisPos.x,thisPos.y + setY });
	clipTransform->SetLocalScale({ 1.9, 1.9 });
}
