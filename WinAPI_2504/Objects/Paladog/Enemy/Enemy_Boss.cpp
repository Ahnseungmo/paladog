#include "Framework.h"

Enemy_Boss::Enemy_Boss():Character({200,200})
{
	horseTransform = new Transform();
	horseTransform->SetParent(this);
	horseTransform->SetTag("horseClip");

	UnitStat stat;
	stat.maxHp = 300;
	stat.attack = 10;
	stat.moveSpeed = 80;
	stat.attackSpeed = 1.0f;
	stat.attackRange = 300;
	stat.attackCount = 1;

	SetStat(stat);
	SetTeam(TeamType::Enemy);

	CreateHorse();
	CreateClips();
}

Enemy_Boss::~Enemy_Boss()
{
}

void Enemy_Boss::Render()
{

	switch (curState)
	{
	case Character::Run:

		worldBuffer->Set(horseTransform->GetWorld());  //horseTransform 위치로 셰이더에 위치 전달 
		worldBuffer->SetVS(0);						//이렇게 버퍼랑 셰이더 이용해서 위치 그릴수도있구나..
		walkingHorse->Render(0);                   //walkingHorse이 horseTransform 위치를 기준으로 그림
		break;
	case Character::Attack:
		worldBuffer->Set(horseTransform->GetWorld());  //horseTransform 위치로 셰이더에 위치 전달 
		worldBuffer->SetVS(0);						//이렇게 버퍼랑 셰이더 이용해서 위치 그릴수도있구나..
		walkingHorse->Render(0);                   //walkingHorse이 horseTransform 위치를 기준으로 그림
		break;
	}
	Character::Render();
}

void Enemy_Boss::Update()
{
	switch (curState)
	{
	case Character::Run:
		walkingHorse->Update(0);
		ChangeTransform();
		break;
	case Character::Attack:
		walkingHorse->Update(0);
		ChangeTransform();
		break;
	case Character::Dead:
		clipTransform->SetLocalScale({0.8f,0.8f});
		break;
	}
	Character::Update();
	horseTransform->UpdateWorld();

}

void Enemy_Boss::PushTarget()
{
	if (!targetList)
		return;

	for (Character* unit : *targetList)
	{
		if (!unit->IsActive() || unit->GetHP() <= 0)
			continue;

		Vector2 unitPos = unit->GetGlobalPosition();
		unit->SetLocalPosition(unitPos.x - 300, unitPos.y);
	}
}

void Enemy_Boss::CreateHorse()
{
	attackHorse = new Quad(L"Resources/Textures/Enemy_Boss/Boss_Attack.png");
	attackHorse->SetParent(this);


	walkingHorse = new CharacterAnimation();
	walkingHorse->LoadClip("Resources/Textures/Enemy_Boss/", "Boss_Walk.xml", true);;

	//walkingHorse->SetParent(this);
}

void Enemy_Boss::CreateClips()
{
	animation->LoadClip("Resources/Textures/Enemy_Boss/", "Boss_Head_Walk.xml", true);
	animation->LoadClip("Resources/Textures/Enemy_Boss/", "Boss_Head_Attack.xml", true);
	animation->LoadClip("Resources/Textures/Enemy_Boss/", "Boss_Dead.xml", false);

	animation->GetClip(Attack)->SetFrameEvent(1, bind(&Character::AttackTarget, this));
	

}

void Enemy_Boss::ChangeTransform()
{
	Vector2 pos = horseTransform->GetLocalPosition();
	if (curState == Run)
	{
		clipTransform->SetLocalPosition(pos.x-100 , pos.y+60);
		clipTransform->SetLocalScale({ 1.5f,1.5f });
		horseTransform->SetLocalScale({ 1.5f,1.5f });
	}
	else
	{
		clipTransform->SetLocalPosition(pos.x , pos.y+30);
		clipTransform->SetLocalScale({ 1.5f,1.5f });
		horseTransform->SetLocalScale({ 1.5f,1.5f });
	}
}
