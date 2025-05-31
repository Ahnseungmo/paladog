#include "Framework.h"
#include "Background.h"

Background::Background(float leftEdge, float rightEdge)
    : leftEdge(leftEdge), rightEdge(rightEdge)
{
    background = new Quad(L"Resources/Textures/Background/background.png");
    Vector2 size = background->GetSize();
    background->SetSize(size * 2.5f);
    background->SetLocalPosition(Vector2(640, 650));

    background->UpdateWorld();
}


Background::~Background()
{
    delete background;
}

void Background::Render()
{
    background->Render();
}
