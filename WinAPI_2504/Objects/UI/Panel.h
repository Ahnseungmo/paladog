#pragma once

class Panel : public Transform
{
public:
    Panel(Vector2 pos);
    ~Panel();

    void AddButton(Button* button);
    void AddCoolTimeButton(Button* button);
    void Update();
    void Render();

    void CreateButtons();
    void CreateCoolTimeButtons();
    GaugeBar* GetSpawnBar() { return spawnBar; }
    GaugeBar* GetManaBar() { return manaBar; }

    void SpawnCharacter(int type);
    void MeatSkill();

    void SetPaladog(Paladog* paladog) { this->paladog = paladog; }

private:
    Quad* panelTexture;
    GaugeBar* spawnBar;
    GaugeBar* manaBar;
    vector<Button*> buttons;
    vector<Button*> coolTimeButtons;
    Paladog* paladog = nullptr;
    float maxCoolTime[5] = { 1, 2, 3, 4, 5 };
    float coolTimeCounts[5] = { 1, 2, 3, 4, 5 };
};





