#pragma once


class Character : public RectCollider
{
protected:
    enum ActionState
    {
        Run, Attack, Dead
    };
public:

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


    virtual void AttackTarget();
    void AttackSpeedBuff();
    void SpeedBuff();

    const UnitStat& GetStat() const { return stat; }
    int GetHP() { return hp; }
    TeamType GetTeam() const { return team; }

    void SetCurStateToRun()
    {
        curState = Run;
    }
    void ResetStat() { SetStat(baseStat); }
    void SetBaseStat(const UnitStat& stat)
    {
        this->baseStat = stat;
        SetStat(stat);
    }
    void SetStat(const UnitStat& stat) {
        this->stat = stat;
        this->hp = stat.maxHp;
    }
    void SetTeam(TeamType team) { this->team = team; }
    void SetTargetList(vector<Character*>* targets) { this->targetList = targets; }
    void SetClipTransform(Vector2 pos){ clipTransform->SetLocalPosition(pos); }

    void TakeDamage(float damage);

protected:
    virtual void CreateClips() = 0;
    void Move();
    void State();
    virtual void Animation();
    void FindTarget();

protected:
    float hp = 100.0f;
    float attackSpeedBuff = 1.0f;
    float speedBuff = 1.0f;

    UnitStat stat;
    UnitStat baseStat;

    ActionState curState = Run;
    TeamType team = TeamType::Ally;

    Character* target = nullptr;
    vector<Character*>* targetList = nullptr;

    Transform* clipTransform;
    MatrixBuffer* worldBuffer;

    CharacterAnimation* animation;
    HealthBar* hpBar;

};