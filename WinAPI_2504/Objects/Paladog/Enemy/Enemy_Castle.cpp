#include "Framework.h"

Enemy_Castle::Enemy_Castle() :Character({ 300,300 })
{
	MappingCharacterData(2001);
	SetTeam(TeamType::Enemy);

	CreateQuad(Alive, L"Resources/Textures/Enemy_Castle/enemy_base_full_front.png", L"Resources/Textures/Enemy_Castle/enemy_base_full_back.png");
	CreateQuad(Damage, L"Resources/Textures/Enemy_Castle/enemy_base_damaged_front.png", L"Resources/Textures/Enemy_Castle/enemy_base_damaged_back.png");
	CreateQuad(Broken, L"Resources/Textures/Enemy_Castle/enemy_base_broken_front.png", L"Resources/Textures/Enemy_Castle/enemy_base_broken_back.png");
	
	SetLocalPosition({ 1600,600 }); //위치설정하기
	UpdateWorld();
	for (auto& frame : frames)
	{
		for (Quad* f : frame.second)
		{
			f->UpdateWorld();
		}
	}
}

Enemy_Castle::~Enemy_Castle()
{
	for (auto& frame : frames)
	{
		for (Quad* f : frame.second)
		{
			delete f;
		}
	}
}

void Enemy_Castle::Update()
{
	CheckHP();
}

void Enemy_Castle::Render()
{
	for (Quad* frame : frames[state])
	{
		frame->Render();
	}
	
	RectCollider::Render();
	hpBar->Render();
	
}

void Enemy_Castle::CreateQuad(CastleStatus status, wstring frontPath, wstring backPath)
{
	Quad* front = new Quad(frontPath);
	Quad* back = new Quad(backPath);

	front->SetParent(this);
	back->SetParent(this);

	front->SetLocalScale({ 1.8, 1.8 });
	back->SetLocalScale({ 1.8, 1.8 });
	
	front->SetLocalPosition(Vector2(-200, -100));
	back->SetLocalPosition(Vector2(-200, -100));

	frames[status].push_back(back);
	frames[status].push_back(front);
}

void Enemy_Castle::CheckHP()
{

	if (hp <= 0.0f)
		state = Broken;
	else if (hp < MAX_HP * 0.6f)
		state = Damage;
	else
		state = Alive;
}


