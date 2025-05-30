#pragma once

class HealthBar
{
public:
    HealthBar(float width = 60.0f, float height = 8.0f, float margin = 20.0f);
    ~HealthBar();

    void Update(Vector2 basePos,float sizeY,float curHp, float maxHp);
    void Render();
    void SetBarColor(float r, float g, float b);

private:
    Quad* background;
    Quad* bar;

    float width;
    float height;
    float margin;
};
