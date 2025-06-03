#pragma once
enum class ALLY_TYPE
{
    Knight = 1001,
    Archer = 1002,
    Boxer = 1003,
    Lancer = 1004,
    Tanker = 1005,
    Elite = 1006,
    Bomber = 1007,
    End
};

class AllyManager : public Singleton<AllyManager>
{
    friend class Singleton<AllyManager>;
private:
    const int UNIT_COUNT = 20;

public:
    AllyManager();
    ~AllyManager();

    void Update();
    void Render();

    void Spawn(ALLY_TYPE type);
    Vector2 RandomPos();

    vector<Character*>* GetAllUnits();
    vector<Character*> ActiveUnits();

    void SetTargetList(vector<Character*>* enemies);
    void CreateUnit();
    Character* GetInactive(ALLY_TYPE type);

    void RegistAlly();
    void AddPalaDog(Character* paladog);

    void UnitOut(Character* unit);

    void ResetUnit();

private:

    unordered_map<ALLY_TYPE, vector<Character*>> totalUnits;
    unordered_map<ALLY_TYPE, function<Character* ()>> unitList;

    vector<Character*>* enemies = nullptr;

    Character* player = nullptr;
};