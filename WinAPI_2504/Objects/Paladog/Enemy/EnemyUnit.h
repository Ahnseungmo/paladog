#pragma once
class EnemyUnit : public Character
{
public:
    EnemyUnit();
    ~EnemyUnit();

protected:
    void CreateClips() override;
};
