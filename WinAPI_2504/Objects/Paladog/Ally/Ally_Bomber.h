#pragma once

class Ally_Bomber : public Character
{
private:
    const int MAX_BOMBS = 5;
public:
    Ally_Bomber();
    ~Ally_Bomber();

    void Update() override;
    void Render() override;
protected:
    void CreateClips() override;
    void Fire();
private:
    vector<Bomb*> bombs;
};