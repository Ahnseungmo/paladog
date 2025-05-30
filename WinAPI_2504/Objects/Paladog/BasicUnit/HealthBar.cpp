#include "Framework.h"

HealthBar::HealthBar(float width, float height, float margin)
	:width(width), height(height), margin(margin)
{
    background = new Quad(L"Resources/Textures/White.png");
    background->SetColor(0.2f, 0.2f, 0.2f);
    background->SetSize(Vector2(width, height));

    bar = new Quad(L"Resources/Textures/White.png");
    bar->SetColor(1.0f, 0.0f, 0.0f);
    bar->SetSize(Vector2(width, height));
}

HealthBar::~HealthBar()
{
    delete background;
    delete bar;
}

void HealthBar::Update(Vector2 basePos,float sizeY, float curHp, float maxHp)
{
    float ratio = (maxHp > 0.0f) ? (curHp / maxHp) : 0.0f;
    ratio = max(0.0f, min(1.0f, ratio));
    float hpWidth = width * ratio;

    Vector2 pos = basePos + Vector2(0, sizeY * 0.5f + height * 0.5f + margin);

    background->SetLocalPosition(pos);
    background->SetSize(Vector2(width, height));

    Vector2 barPos = pos + Vector2(-(width - hpWidth) * 0.5f, 0);
    bar->SetLocalPosition(barPos);
    bar->SetSize(Vector2(hpWidth, height));

    background->UpdateWorld();
    bar->UpdateWorld();
}

void HealthBar::Render()
{
    background->Render();
    bar->Render();
}

void HealthBar::SetBarColor(float r,float g,float b)
{
    bar->SetColor(r, g, b);
}
