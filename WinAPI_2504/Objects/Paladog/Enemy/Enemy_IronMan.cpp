#include "Framework.h"

Enemy_IronMan::Enemy_IronMan():Character({130,200})
{
	UnitStat stat;
	stat.maxHp = 400;
	stat.attack = 0.005f;
	stat.moveSpeed = 80;
	stat.attackSpeed = 1.0f;
	stat.attackRange = 100;
	stat.attackCount = 1;

	
	SetStat(stat);
	SetTeam(TeamType::Enemy);
	CreateClips();
	CreateBeam();
}

Enemy_IronMan::~Enemy_IronMan()
{

}

void Enemy_IronMan::Update()
{

	IsSpecial();
	CheckTimer();
	Character::Update();
	BeamUpdate();
}

void Enemy_IronMan::Render()
{
	Character::Render();
	beamCollider->Render();
	beam->Render();
}

void Enemy_IronMan::AttackTarget()
{
	attackCount++;
	if (attackCount > ATTACK_COUNT)
	{
		beamCollider->SetActive(true);
		beam->SetActive(true);
		isSpecial = true;

	}
	else if (!isSpecial)
		Character::AttackTarget();
}

void Enemy_IronMan::CreateBeam()
{
	beam = new Quad(L"Resources/Textures/Enemy/IronMan_Beam.png");
	beamCollider = new RectCollider({ 400,40 });

	beam->SetParent(beamCollider);
	beam->SetLocalScale({ 0.2,0.3 });

	beamCollider->SetActive(false);
	beam->SetActive(false);
}

void Enemy_IronMan::CreateClips()
{
	float setY = Size().y * 0.5f - 30;
	Vector2 thisPos = GetLocalPosition();

	animation->LoadClip("Resources/Textures/Enemy/", "IronMan_Walk.xml", true);
	animation->LoadClip("Resources/Textures/Enemy/", "IronMan_Attack.xml", true);
	animation->LoadClip("Resources/Textures/Enemy/", "IronMan_Dead.xml", false);

	animation->GetClip(Attack)->SetFrameEvent(7, bind(&Character::AttackTarget, this));

	clipTransform->SetLocalPosition({ thisPos.x,thisPos.y + setY - 30 });
	clipTransform->SetLocalScale({ 1.9, 1.9 });
}

void Enemy_IronMan::BeamUpdate()
{
	Vector2 pos = GetGlobalPosition();
	float halfX = beamCollider->Size().x * 0.5f;
	beamCollider->SetLocalPosition({pos.x-halfX,pos.y});
	beamCollider->UpdateWorld();
	beam->UpdateWorld();
}

void Enemy_IronMan::CheckTimer()
{
	if (!isSpecial) return;
	timer += DELTA;
	UpDownMove();
	if (timer > BEAM_TIME)
	{
		isSpecial = false;
		beam->SetActive(false);
		beamCollider->SetActive(false);
		timer = 0.0f;
	}
}

void Enemy_IronMan::UpDownMove()
{
	float halfTime = BEAM_TIME * 0.5f;
	if (timer < halfTime)
		Translate(Vector2::Up() * MOVE_SPEED * DELTA);
	else
		Translate(Vector2::Down() * MOVE_SPEED * DELTA);
}

void Enemy_IronMan::IsSpecial()
{
	if (!isSpecial)
		return;

	if (!targetList)
		return;


	for (Character* unit : *targetList)
	{
		if (!unit->IsActive())
			continue;

		if (beamCollider->IsRectCollision(unit, nullptr))
		{
			unit->TakeDamage(stat.attack);
		}
	}

}
