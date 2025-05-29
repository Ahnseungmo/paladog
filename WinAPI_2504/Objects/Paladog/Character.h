#pragma once
#pragma once

struct UnitStat
{
    float maxHp = 100.0f;
    float attack = 10.0f;
    float moveSpeed = 100.0f;
    float attackSpeed = 1.0f;
    float attackRange = 50.0f;
    int attackCount = 1;
};

class Character : public RectCollider
{
protected:
    const float HPBAR_WIDTH = 60.0f;
    const float HPBAR_HEIGHT = 8.0f;
    const float HPBAR_POS = 0.6f;

    enum ActionState
    {
        Run, Attack, Dead
    };

    enum class TeamType
    {
        Ally, Enemy
    };

public:
    Character(Vector2 size = Vector2(100, 100));
    virtual ~Character();

    virtual void Update();
    virtual void Render();
    virtual void Edit();

    void SetStat(const UnitStat& stat) {
        this->stat = stat;
        this->hp = stat.maxHp;
    }
    const UnitStat& GetStat() const { return stat; }

    void SetTeam(TeamType team) { this->team = team; }
    TeamType GetTeam() const { return team; }

    void SetTargetList(vector<Character*>* targets) { this->targetList = targets; }

protected:
    virtual void CreateClips() = 0;
    virtual void LoadClip(string path, string file, bool isLoop, float speed = 1.0f);
    virtual void LoadClip(string path, string file, string file2, bool isLoop, float speed = 1.0f);

    void Move();
    void State();
    virtual void Animation();

    virtual void FindTarget();
    virtual void AttackTarget();

    void TakeDamage(float damage);

    void CreateHPBar();
    void UpdateHPBar();
    void RenderHPBar();

protected:
    float hp = 100.0f;
    float attackTimer = 0.0f;
    UnitStat stat;

    ActionState curState = Run;
    TeamType team = TeamType::Ally;

    Character* target = nullptr;
    vector<Character*>* targetList = nullptr;

    Transform* clipTransform;
    MatrixBuffer* worldBuffer;
    vector<Clip*> clips;

    Quad* background;
    Quad* hpBar;
};