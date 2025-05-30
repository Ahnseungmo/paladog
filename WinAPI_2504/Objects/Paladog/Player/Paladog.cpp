#include "Framework.h"

Paladog::Paladog()
{
    paladogTexture = new Quad(L"Resources/Textures/Paladog/TestPlayer.png");
    paladogTexture->SetParent(this);
    auraTexture = new Quad(L"Resources/Textures/Paladog/Aura.png");
    auraTexture->SetParent(this);
    auraCollider = new RectCollider(Vector2(213, 58));
    auraCollider->SetParent(auraTexture);
    punch = new Punch(Vector2(90, 30));
    punch->SetParent(this);
    punch->SetActive(false);
}

Paladog::~Paladog()
{
	delete paladogTexture;
    delete auraTexture;
    delete auraCollider;
    delete punch;
}

void Paladog::Update()
{
    //if (Input::Get()->IsKeyPress('W')) // �׽�Ʈ��
    //    Translate(Vector2::Up() * SPEED * DELTA);
    //if (Input::Get()->IsKeyPress('S'))
    //    Translate(Vector2::Down() * SPEED * DELTA);
    if (this->GetGlobalPosition().x > 300 && Input::Get()->IsKeyPress('A'))
        Translate(Vector2::Left() * SPEED * DELTA);
    if (this->GetGlobalPosition().x < SCREEN_WIDTH && Input::Get()->IsKeyPress('D'))
        Translate(Vector2::Right() * SPEED * DELTA);

    //PunchSkill();
    punch->Update();

    if (punch->IsActive() && punch->GetGlobalPosition().x > SCREEN_WIDTH + 600)
    {
        punch->SetActive(false);
        punch->SetLocalPosition(Vector2(0, 0));
    }
    auraCollider->UpdateWorld();
    auraTexture->UpdateWorld();
    paladogTexture->UpdateWorld();
    UpdateWorld();
}


void Paladog::Render()
{
    auraCollider->Render();
    punch->Render();
    paladogTexture->Render();
    Collider::Render();
}

void Paladog::AuraRender()
{
    auraTexture->Render();
}

void Paladog::PunchSkill()
{
    punch->SetActive(true);
}
