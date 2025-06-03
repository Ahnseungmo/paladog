#include "Framework.h"

AllyManager::AllyManager()
{
    RegistAlly();
    CreateUnit();
}

AllyManager::~AllyManager()
{
    for (auto it = totalUnits.begin(); it != totalUnits.end(); ++it)
    {
        vector<Character*>& units = it->second;
        for (int i = 0; i < units.size(); i++)
            delete units[i];
    }
}

void AllyManager::Update()
{
    for (auto it = totalUnits.begin(); it != totalUnits.end(); ++it)
    {
        vector<Character*>& units = it->second;
        for (int i = 0; i < units.size(); i++)
        {
            if (units[i]->IsActive())
                units[i]->Update();
            UnitOut(units[i]);
        }
    }
}

void AllyManager::Render()
{
    for (auto it = totalUnits.begin(); it != totalUnits.end(); ++it)
    {
        vector<Character*>& units = it->second;
        for (int i = 0; i < units.size(); i++)
        {
            if (units[i]->IsActive())
                units[i]->Render();
        }
    }
}

void AllyManager::Spawn(ALLY_TYPE type)
{
    if (totalUnits.count(type) == 0)
        return;

    vector<Character*>& units = totalUnits[type];

    for (int i = 0; i < units.size(); i++)
    {
        Character* unit = units[i];

        if (!unit->IsActive())
        {
            unit->ResetStat();
            unit->SetLocalPosition(RandomPos());
            unit->SetTargetList(enemies);
            unit->SetTeam(Character::TeamType::Ally);
            unit->SetCurStateToRun();
            unit->SetIsSpeedBuff(false);
            unit->SetIsAttackSpeedBuff(false);
            unit->SetActive(true);
            break;
        }
    }
}

void AllyManager::CreateUnit()
{
    for (auto it = unitList.begin(); it != unitList.end(); ++it)
    {
        ALLY_TYPE type = it->first;
        function<Character* ()> factory = it->second;

        for (int i = 0; i < UNIT_COUNT; i++)
        {
            Character* unit = factory();
            unit->SetActive(false);
            if (enemies != nullptr)
                unit->SetTargetList(enemies);
            totalUnits[type].push_back(unit);
        }
    }
}

Character* AllyManager::GetInactive(ALLY_TYPE type)
{
    if (totalUnits.count(type) == 0)
        return nullptr;

    vector<Character*>& units = totalUnits[type];
    for (int i = 0; i < units.size(); i++)
    {
        if (!units[i]->IsActive())
            return units[i];
    }

    return nullptr;
}

Vector2 AllyManager::RandomPos()
{
    float x = -300;
    float y = 500 + rand() % 100;
    return Vector2(x, y);
}

vector<Character*>* AllyManager::GetAllUnits()
{
    static vector<Character*> allUnits;
    allUnits.clear();

    unordered_map<ALLY_TYPE, vector<Character*>>::iterator it;
    for (it = totalUnits.begin(); it != totalUnits.end(); ++it)
    {
        vector<Character*>& units = it->second;
        for (int i = 0; i < units.size(); i++)
        {
            allUnits.push_back(units[i]);
        }
    }
    if (player != nullptr)
        allUnits.push_back(player);

    return &allUnits;
}

vector<Character*> AllyManager::ActiveUnits()
{
    vector<Character*> result;

    unordered_map<ALLY_TYPE, vector<Character*>>::iterator it;
    for (it = totalUnits.begin(); it != totalUnits.end(); ++it)
    {
        vector<Character*>& units = it->second;
        for (int i = 0; i < units.size(); ++i)
        {
            if (units[i]->IsActive())
                result.push_back(units[i]);
        }
    }

    return result;
}

void AllyManager::SetTargetList(vector<Character*>* enemies)
{
    this->enemies = enemies;

    for (auto it = totalUnits.begin(); it != totalUnits.end(); ++it)
    {
        vector<Character*>& units = it->second;
        for (int i = 0; i < units.size(); i++)
        {
            if (units[i]->IsActive())
                units[i]->SetTargetList(enemies);
        }
    }
}

void AllyManager::RegistAlly()
{
    unitList[ALLY_TYPE::Knight] = []() { return new Ally_Knight(); };
    unitList[ALLY_TYPE::Archer] = []() { return new Ally_Archer(); };
    unitList[ALLY_TYPE::Boxer] = []() { return new Ally_Boxer(); };
    unitList[ALLY_TYPE::Lancer] = []() { return new Ally_Lancer(); };
    unitList[ALLY_TYPE::Tanker] = []() { return new Ally_Tanker(); };
    unitList[ALLY_TYPE::Elite] = []() { return new Ally_Elite(); };
    unitList[ALLY_TYPE::Bomber] = []() { return new Ally_Bomber(); };
}

void AllyManager::AddPalaDog(Character* paladog)
{
    player = paladog;
}

void AllyManager::UnitOut(Character* unit)
{
    if (!unit->IsActive()) return;

    Vector2 pos = unit->GetGlobalPosition();
    if (pos.x < 1780)
        return;
    SceneManager::Get()->ChangeScene("GameClear");
}

void AllyManager::ResetUnit()
{

    for (auto it = totalUnits.begin(); it != totalUnits.end(); ++it)
    {
        vector<Character*>& units = it->second;
        for (int i = 0; i < units.size(); i++)
        {
            units[i]->SetActive(false);
            units[i]->ResetStat();
            units[i]->SetLocalPosition({ 0,0 });
            units[i]->UpdateWorld();
        }
    }

}