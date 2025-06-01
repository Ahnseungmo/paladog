#include "Framework.h"

Paladog::Paladog()
{
    UnitStat stat;
    stat.maxHp = 5000;
    stat.attack = 60;
    stat.moveSpeed = SPEED;
    stat.attackSpeed = 0;
    stat.attackRange = 0;
    stat.attackCount = 0;
    SetBaseStat(stat);
    SetTeam(TeamType::Ally);

    paladogTexture = new Quad(L"Resources/Textures/Paladog/TestPlayer.png");
    paladogTexture->SetParent(this);
    auraTexture = new Quad(L"Resources/Textures/Paladog/Aura.png");
    auraTexture->SetParent(this);
    auraCollider = new RectCollider(Vector2(213, 58));
    auraCollider->SetParent(auraTexture);
    punch = new Punch(Vector2(90, 30));
    punch->SetParent(this);
    punch->SetActive(false);
    hpBar->SetBarColor(0, 1, 0);
    CreateClips();
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
    //if (Input::Get()->IsKeyPress('W')) // 테스트용
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

    AuraBuff();

    auraCollider->UpdateWorld();
    auraTexture->UpdateWorld();
    paladogTexture->UpdateWorld();
    hpBar->Update(GetGlobalPosition(), Size().y, hp, stat.maxHp);
    UpdateWorld();
}


void Paladog::Render()
{
    auraCollider->Render();
    punch->Render();
    paladogTexture->Render();
    hpBar->Render();
    Collider::Render();
}

void Paladog::AuraRender()
{
    auraTexture->Render();
}

void Paladog::AuraBuff()
{
    vector<Character*>* allies = AllyManager::Get()->GetAllUnits();

    float auraX = auraCollider->GetGlobalPosition().x;
    float auraHalfWidth = auraCollider->Size().x * 0.5f;
    float left = auraX - auraHalfWidth;
    float right = auraX + auraHalfWidth;

    for (int i = 0; i < allies->size(); i++)
    {
        Character* unit = (*allies)[i];
        if (!unit->IsActive())
            continue;

        float unitX = unit->GetGlobalPosition().x;
        if (unitX >= left && unitX <= right) {
            unit->SpeedBuff(SPEEDBUFF);
            unit->AttackSpeedBuff(ATTACK_SPEEDBUFF);
        }
        else {
            unit->ResetSpeedBuff(SPEEDBUFF);
            unit->ResetAttackSpeedBuff(ATTACK_SPEEDBUFF);
        }
    }
}

void Paladog::PunchSkill()
{
    punch->SetActive(true);
}

void Paladog::CreateClips()
{
}
