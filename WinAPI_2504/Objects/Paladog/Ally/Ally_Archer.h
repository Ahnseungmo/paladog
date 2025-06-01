#pragma once
class Ally_Archer : public Character
{
private:
    const int MAX_ARROW = 3;
public:
    Ally_Archer();
    ~Ally_Archer();

    void Update() override;
    void Render() override;
protected:
    void CreateClips() override;
    void Fire();
private:
    vector<Allow*> allows;

};

