#include "Framework.h"

Ally_Knight::Ally_Knight()
{
	UnitStat stat = { 50,20,100,1.0f,80,1 };
	SetStat(stat);
	SetTeam(TeamType::Ally);
	CreateClips();


}

Ally_Knight::~Ally_Knight()
{
}

void Ally_Knight::CreateClips()
{
	animation->LoadClip("Resources/Textures/Ally_Knight/", "Ally_Knight_Walk.xml", true);
	animation->LoadClip("Resources/Textures/Ally_Knight/", "Ally_Knight_Attack.xml", true);
	animation->LoadClip("Resources/Textures/Ally_Knight/", "Ally_Knight_Dead.xml", false);
}
