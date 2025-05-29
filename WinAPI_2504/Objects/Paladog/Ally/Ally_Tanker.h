#pragma once
class Ally_Tanker : public Character
{
public:
    Ally_Tanker();
    ~Ally_Tanker();

protected:
    void CreateClips() override;
};