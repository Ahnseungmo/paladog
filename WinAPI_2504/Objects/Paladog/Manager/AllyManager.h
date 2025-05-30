#pragma once
enum class ALLY_TYPE
{
    Knight,
    Archer,
    Boxer,
    Lancer,
    Tanker,
    Elite,
    End
};

class AllyManager : public Singleton<AllyManager>
{
    friend class Singleton<AllyManager>;

public:
    AllyManager();
    ~AllyManager();

    void Update();
    void Render();

    void Spawn(ALLY_TYPE type);
    Vector2 RandomPos();

    vector<Character*>* GetAllUnits();
    void SetTargetList(vector<Character*>* enemies);
    void CreateUnit();
    Character* GetInactive(ALLY_TYPE type);

    void RegistAlly();

private:
    const int UNIT_COUNT = 20;

    unordered_map<ALLY_TYPE, vector<Character*>> totalUnits;
    unordered_map<ALLY_TYPE, function<Character* ()>> unitList;

    vector<Character*>* enemies = nullptr;
};