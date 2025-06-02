#include "Framework.h"

Ally_Archer::Ally_Archer() : Character(Vector2(140, 140))
{
    MappingAllyData((int)ALLY_TYPE::Archer);
    SetBaseStat(stat);
    SetTeam(TeamType::Ally);
    CreateClips();
    hpBar->SetBarColor(0, 1, 0);

    for (int i = 0; i < MAX_ARROW; ++i)
    {
        Allow* arrow = new Allow();
        arrow->SetActive(false);
        allows.push_back(arrow);
    }
}

Ally_Archer::~Ally_Archer()
{
    for (int i = 0; i < allows.size(); i++)
        delete allows[i];
}

void Ally_Archer::Update()
{
    if (curState != Dead)
        State();

    for (int i = 0; i < allows.size(); i++)
        allows[i]->Update();

    Animation();
    clipTransform->UpdateWorld();
    hpBar->Update(GetGlobalPosition(), Size().y, hp, stat.maxHp);
    UpdateWorld();
}

void Ally_Archer::Render()
{
    Collider::Render();

    for (int i = 0; i < allows.size(); i++)
        allows[i]->Render();

    worldBuffer->Set(clipTransform->GetWorld());
    worldBuffer->SetVS(0);
    if (curState == Stun)
        animation->Render(Attack);
    else
        animation->Render(curState);
    hpBar->Render();
}

void Ally_Archer::CreateClips()
{
    Vector2 pos = GetLocalPosition();

    animation->LoadClip("Resources/Textures/Ally_Archer/", "Ally_Archer_Walk.xml", true);
    animation->LoadClip("Resources/Textures/Ally_Archer/", "Ally_Archer_Attack.xml", true, stat.attackSpeed);
    animation->LoadClip("Resources/Textures/Ally_Archer/", "Ally_Archer_Dead.xml", false);

    animation->GetClip(Attack)->SetFrameEvent(14, bind(&Ally_Archer::Fire, this));
    
    clipTransform->SetLocalPosition({ pos.x,pos.y + 90.0f });
}

void Ally_Archer::Fire()
{
    if (!target || !target->IsActive())
        return;

    for (int i = 0; i < allows.size(); i++)
    {
        if (!allows[i]->IsActive())
        {
            allows[i]->Fire(GetGlobalPosition(), target);
            break;
        }
    }
}





