#pragma once


class Character : public RectCollider
{
protected:
    enum ActionState
    {
        Run, Attack, Dead, Stun
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
    virtual void Fire() {};

    void AttackSpeedBuff(float percent);
    void ResetAttackSpeedBuff(float percent);
    void SpeedBuff(float percent);
    void ResetSpeedBuff(float percent);

    const UnitStat& GetStat() const { return stat; }
    int GetHP() { return hp; }
    int GetMaxHP() { return stat.maxHp; }
    void SetHP(int hp) { this->hp = hp; }
    TeamType GetTeam() const { return team; }

    void SetCurStateToRun()
    {
        curState = Run;
    }
    void SetCurStateToStun()
    {
        curState = Stun;
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
    void SetClipTransform(Vector2 pos) { clipTransform->SetLocalPosition(pos); }
    void SetIsSpeedBuff(bool is) { isSpeedBuff = is; }
    void SetIsAttackSpeedBuff(bool is) { isAttackSpeedBuff = is; }

    void TakeDamage(float damage);

    void TargetToRun();
    void TargetToStun();

protected:
    virtual void CreateClips() = 0;
    void Move();
    void State();
    virtual void Animation();
    void FindTarget();
    vector<Character*> FindTargetRange(int maxCount);

protected:
    float hp = 100.0f;
    bool isAttackSpeedBuff = false;
    bool isSpeedBuff = false;

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