#include "Framework.h"

Ally_Tanker::Ally_Tanker()
{
	MappingAllyData((int)ALLY_TYPE::Tanker);
	SetBaseStat(stat);
	SetTeam(TeamType::Ally);
	CreateClips();
	hpBar->SetBarColor(0, 1, 0);
}

Ally_Tanker::~Ally_Tanker()
{

}

void Ally_Tanker::CreateClips()
{
	Vector2 pos = GetLocalPosition();
	animation->LoadClip("Resources/Textures/Ally_Tanker/", "Ally_Tanker_Walk.xml", true);
	animation->LoadClip("Resources/Textures/Ally_Tanker/", "Ally_Tanker_Attack.xml", true, stat.attackSpeed);
	animation->LoadClip("Resources/Textures/Ally_Tanker/", "Ally_Tanker_Dead.xml", false);

	animation->GetClip(Attack)->SetFrameEvent(16, bind(&Ally_Tanker::Recovery, this));

	clipTransform->SetLocalPosition({ pos.x,pos.y + 85.0f });
}

void Ally_Tanker::Recovery()
{
	if (target && target->IsActive()) {
		hp += stat.maxHp*0.25f;
		if (hp > stat.maxHp) {
			hp = stat.maxHp;
		}
		target->TakeDamage(stat.attack);
	}
		
}
