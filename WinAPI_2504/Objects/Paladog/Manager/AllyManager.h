#pragma once
enum class ALLY_TYPE
{
    Knight,
    Archer,
    Boxer,
    Lancer,
    Tanker,
    Elite,
    Bomber,
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
    void SetTargetList(vector<Character*>* enemies);
    void CreateUnit();
    Character* GetInactive(ALLY_TYPE type);

    void RegistAlly();
private:

    unordered_map<ALLY_TYPE, vector<Character*>> totalUnits;
    unordered_map<ALLY_TYPE, function<Character* ()>> unitList;

    vector<Character*>* enemies = nullptr;
};