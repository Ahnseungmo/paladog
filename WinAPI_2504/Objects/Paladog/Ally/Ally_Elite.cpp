#include "Framework.h"

Ally_Elite::Ally_Elite() : Character(Vector2(150, 180))
{
	MappingAllyData((int)ALLY_TYPE::Elite);
	SetBaseStat(stat);
	SetTeam(TeamType::Ally);
	CreateClips();
	hpBar->SetBarColor(0, 1, 0);
}

Ally_Elite::~Ally_Elite()
{
}

void Ally_Elite::CreateClips()
{
	Vector2 pos = GetLocalPosition();

	animation->LoadClip("Resources/Textures/Ally_Elite/", "Ally_Elite_Walk.xml", true);
	animation->LoadClip("Resources/Textures/Ally_Elite/", "Ally_Elite_Attack1.xml", "Ally_Elite_Attack2.xml", true, stat.attackSpeed);
	animation->LoadClip("Resources/Textures/Ally_Elite/", "Ally_Elite_Dead.xml", false);

	animation->GetClip(Attack)->SetFrameEvent(7, bind(&Character::AttackTarget, this));
	animation->GetClip(Attack)->SetFrameEvent(22, bind(&Character::AttackTarget, this));

	clipTransform->SetLocalPosition({ pos.x,pos.y + 65.0f });
}
