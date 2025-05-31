#pragma once

class Background
{
public:
    Background(float leftEdge, float rightEdge);
    ~Background();

    void Render();

private:
    Quad* background;
    float leftEdge, rightEdge;
};
