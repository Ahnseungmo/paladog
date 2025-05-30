#pragma once

class Panel : public Transform
{
public:
    Panel(wstring imagePath, Vector2 pos);
    ~Panel();

    void AddButton(Button* button);
    void Update();
    void Render();

    void CreateButtons();

private:
    Quad* quad;
    vector<Button*> buttons;
};

