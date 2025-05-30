#pragma once

class Ally_Bomber : public Character
{
public:
    Ally_Bomber();
    ~Ally_Bomber();

protected:
    void CreateClips() override;
};