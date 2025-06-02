#include "Framework.h"

Ally_Knight::Ally_Knight()
{
	MappingAllyData((int)ALLY_TYPE::Knight);
	SetBaseStat(stat);
	SetTeam(TeamType::Ally);
	CreateClips();
	hpBar->SetBarColor(0, 1, 0);


}

Ally_Knight::~Ally_Knight()
{
}

void Ally_Knight::CreateClips()
{
	Vector2 pos = GetLocalPosition();

	animation->LoadClip("Resources/Textures/Ally_Knight/", "Ally_Knight_Walk.xml", true);
	animation->LoadClip("Resources/Textures/Ally_Knight/", "Ally_Knight_Attack.xml", true, stat.attackSpeed);
	animation->LoadClip("Resources/Textures/Ally_Knight/", "Ally_Knight_Dead.xml", false);

	animation->GetClip(Attack)->SetFrameEvent(6, bind(&Character::AttackTarget, this));
	animation->GetClip(Attack)->SetFrameEvent(10, bind(&Character::AttackTarget, this));

	clipTransform->SetLocalPosition({ pos.x,pos.y + 110.0f });
}
