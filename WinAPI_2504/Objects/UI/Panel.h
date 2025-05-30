#pragma once

class Panel : public Transform
{
public:
    Panel(Vector2 pos);
    ~Panel();

    void AddButton(Button* button);
    void Update();
    void Render();

    void CreateButtons();
    SpawnBar* GetBar() { return spawnBar; }
    void SpawnCharacter(int type);

private:
    Quad* panelTexture;
    SpawnBar* spawnBar;
    vector<Button*> buttons;
};





