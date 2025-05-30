#pragma once
class Ally_Tanker : public Character
{
public:
    Ally_Tanker();
    ~Ally_Tanker();

    void Recovery();

protected:
    void CreateClips() override;
};