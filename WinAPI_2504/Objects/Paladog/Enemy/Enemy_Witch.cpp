#include "Framework.h"

Enemy_Witch::Enemy_Witch()
{
	MappingCharacterData(2006);
	SetTeam(TeamType::Enemy);
	CreateClips();
}

Enemy_Witch::~Enemy_Witch()
{
}

void Enemy_Witch::AttackTarget()
{
	specialAttackCount++;
	if (specialAttackCount >= 3)
	{
		SpecialAttack();
		specialAttackCount = 0;
	}
	else
		Character::AttackTarget();

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

void Enemy_Witch::SpecialAttack()
{
	vector<Character*>* enemies = EnemyManager::Get()->GetAllUnits();

	for (Character* enemy : *enemies)
	{
		if (EnemyManager::Get()->IsCastle(enemy))
			continue;
		if (enemy->GetMaxHP() < enemy->GetHP() + ADD_HP)
			enemy->SetHP(enemy->GetMaxHP());
		else
			enemy->SetHP(enemy->GetHP() + ADD_HP);
	}
}
