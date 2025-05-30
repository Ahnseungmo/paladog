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

private:
    float cost = 50.0f;
    Quad* panelTexture;
    SpawnBar* spawnBar;
    vector<Button*> buttons;
};


