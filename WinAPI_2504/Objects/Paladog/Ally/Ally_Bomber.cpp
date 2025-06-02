#include "Framework.h"

Ally_Bomber::Ally_Bomber()
{
    MappingAllyData((int)ALLY_TYPE::Bomber);
    SetBaseStat(stat);
    SetTeam(TeamType::Ally);
    CreateClips();
    hpBar->SetBarColor(0, 1, 0);

    for (int i = 0; i < MAX_BOMBS; ++i)
    {
        Bomb* bomb = new Bomb();
        bomb->SetActive(false);
        bombs.push_back(bomb);
    }
}

Ally_Bomber::~Ally_Bomber()
{
    for (int i = 0; i < bombs.size(); i++)
        delete bombs[i];
}

void Ally_Bomber::Update()
{
    if (curState != Dead)
        State();

    for (int i = 0; i < bombs.size(); i++)
        bombs[i]->Update();

    Animation();
    clipTransform->UpdateWorld();
    hpBar->Update(GetGlobalPosition(), Size().y, hp, stat.maxHp);
    UpdateWorld();
}

void Ally_Bomber::Render()
{
    Collider::Render();

    for (int i = 0; i < bombs.size(); i++)
        bombs[i]->Render();

    worldBuffer->Set(clipTransform->GetWorld());
    worldBuffer->SetVS(0);

    if (curState == Stun)
        animation->Render(Attack);
    else
        animation->Render(curState);
    hpBar->Render();
}

void Ally_Bomber::CreateClips()
{
    Vector2 pos = GetLocalPosition();

    animation->LoadClip("Resources/Textures/Ally_Bomber/", "Ally_Bomber_Walk.xml", true);
    animation->LoadClip("Resources/Textures/Ally_Bomber/", "Ally_Bomber_Attack.xml", true, stat.attackSpeed);
    animation->LoadClip("Resources/Textures/Ally_Bomber/", "Ally_Bomber_Dead.xml", false);

    animation->GetClip(Attack)->SetFrameEvent(6, bind(&Ally_Bomber::Fire, this));

    clipTransform->SetLocalPosition({ pos.x,pos.y + 90.0f });
}

void Ally_Bomber::Fire()
{
    vector<Character*> targets = FindTargetRange(stat.attackCount);

    if (targets.empty())
        return; 

    for (int i = 0; i < bombs.size(); i++)
    {
        if (!bombs[i]->IsActive())
        {
            bombs[i]->Fire(GetGlobalPosition(), targets);
            break;
        }
    }
}
