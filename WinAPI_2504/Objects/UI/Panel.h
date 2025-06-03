#pragma once

class Panel : public Transform
{
private:
    const float HEAL_COST = 50.0f;
    const float HEAL_AMOUNT = 50.0f;
public:
    Panel(Vector2 pos);
    ~Panel();

    void Start();

    void AddButton(Button* button);

    void Update();
    void Render();
	void GUIRender();

    void CreateButtons();
	void CreateCoolTimeButtons();
    void AddCoolTimeButton(CoolTimeButton* coolTimeButton);
    GaugeBar* GetSpawnBar() { return spawnBar; }
    GaugeBar* GetManaBar() { return manaBar; }

    void SpawnCharacter(int type);
    void MeatSkill();
    void HealSkill();

    void SetPaladog(Paladog* paladog) { this->paladog = paladog; }
    
    void ResetGauge();

private:
    Quad* panelTexture;
    GaugeBar* spawnBar;
    GaugeBar* manaBar;

    vector<Button*> buttons;
    vector<CoolTimeButton*> coolTimeButtons;
    vector<int>& deck = DataManager::Get()->GetDeck();

    Paladog* paladog = nullptr;
    float maxCoolTime[7];
    float coolTimeCounts[7];

    HealthBar* hpBar;
    ImFont* fontLarge = nullptr;
};
