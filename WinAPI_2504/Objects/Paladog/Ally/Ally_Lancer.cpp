#include "Framework.h"

Ally_Lancer::Ally_Lancer() : Character(Vector2(120, 150))
{
	MappingAllyData((int)ALLY_TYPE::Lancer);
	SetBaseStat(stat);
	SetTeam(TeamType::Ally);
	CreateClips();
	hpBar->SetBarColor(0, 1, 0);
}

Ally_Lancer::~Ally_Lancer()
{
}

void Ally_Lancer::CreateClips()
{
	Vector2 pos = GetLocalPosition();
	animation->LoadClip("Resources/Textures/Ally_Lancer/", "Ally_Lancer_Walk.xml", true);
	animation->LoadClip("Resources/Textures/Ally_Lancer/", "Ally_Lancer_Attack1.xml", "Ally_Lancer_Attack2.xml", true, stat.attackSpeed);
	animation->LoadClip("Resources/Textures/Ally_Lancer/", "Ally_Lancer_Dead.xml", false);

	animation->GetClip(Attack)->SetFrameEvent(8, bind(&Character::AttackTarget, this));
	animation->GetClip(Attack)->SetFrameEvent(23, bind(&Character::AttackTarget, this));

	clipTransform->SetLocalPosition({ pos.x,pos.y + 85.0f });
}
