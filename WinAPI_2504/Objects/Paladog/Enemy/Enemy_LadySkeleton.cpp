#include "Framework.h"

Enemy_LadySkeleton::Enemy_LadySkeleton()
{
	MappingCharacterData(2004);
	SetTeam(TeamType::Enemy);
	CreateClips();

	CreateBones();
}

Enemy_LadySkeleton::~Enemy_LadySkeleton()
{
	for (Weapon& bone : bones)
	{
		delete bone.weapon;
	}
}

void Enemy_LadySkeleton::Update()
{
	MoveBone();
	boneAni->Update(0);

	Character::Update();
}

void Enemy_LadySkeleton::AttackTarget()
{
	for (Weapon& bone : bones)
	{
		if (!bone.weapon->IsActive())
		{
			bone.weapon->SetActive(true);
			bone.weapon->SetLocalPosition(GetGlobalPosition());

			return;
		}
	}
}

void Enemy_LadySkeleton::Render()
{
	for (Weapon& bone : bones)
	{
		if (!bone.weapon->IsActive()) continue;

		worldBuffer->Set(bone.weapon->GetWorld());
		worldBuffer->SetVS(0);
		boneAni->Render(0);

		bone.weapon->Render();
	}
	Character::Render();

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

void Enemy_LadySkeleton::CreateBones()
{
	boneAni = new CharacterAnimation();
	boneAni->LoadClip("Resources/Textures/Enemy/", "LadySkeleton_Bone.xml", true);

	bones.resize(WEAPON_POOLING);

	for (Weapon& bone : bones)
	{
		//bone = new Weapon;
		bone.weapon = new RectCollider();

		bone.weapon->SetActive(false);
	}
}

void Enemy_LadySkeleton::MoveBone()
{
	for (Weapon& bone : bones)
	{
		if (!bone.weapon->IsActive())
			continue;
		bone.weapon->Translate(Vector2::Left() * BONE_SPEED * DELTA);
		bone.weapon->SetLocalScale({ 1.2, 1.2 });
		bone.weapon->UpdateWorld();

		AttackUnit(bone);
	}

}

void Enemy_LadySkeleton::AttackUnit(Weapon& bone)
{
	for (Character* target : *targetList)
	{
		if (!target->IsActive() || target->GetHP() <= 0)
			continue;

		if (bone.hitTarget.count(target) > 0) continue;


		if (bone.weapon->IsRectCollision(target, nullptr))
		{
			target->TakeDamage(stat.attack);
			bone.hitTarget.insert(target);
			bone.collisionCount++;

			if (bone.collisionCount > MAX_COLLISION)
			{
				bone.weapon->SetActive(false);
				bone.hitTarget.clear();
				bone.collisionCount = 0;
			}
		}
	}
	
}

