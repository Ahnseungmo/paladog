#include "Framework.h"

Camera::Camera()
{
    tag = "Camera";
    viewBuffer = new MatrixBuffer();
}

Camera::~Camera()
{
    delete viewBuffer;
}

void Camera::Update()
{
    if (target)
        FollowMode(target->GetGlobalPosition(), 0.1f);
    else
        FreeMode();

    UpdateWorld();

    viewBuffer->Set(view);
    viewBuffer->SetVS(1);
}

void Camera::SetLimits(float left, float right) 
{
    leftLimit = left;
    rightLimit = right;
}

void Camera::FreeMode()
{
    if (Input::Get()->IsKeyPress(VK_RBUTTON))
    {
        if (Input::Get()->IsKeyPress('W'))
            Translate(Vector2::Up() * speed * DELTA);
        if (Input::Get()->IsKeyPress('S'))
            Translate(Vector2::Down() * speed * DELTA);
        if (Input::Get()->IsKeyPress('A'))
            Translate(Vector2::Left() * speed * DELTA);
        if (Input::Get()->IsKeyPress('D'))
            Translate(Vector2::Right() * speed * DELTA);
    }

    view = XMMatrixInverse(nullptr, world);
}

void Camera::FollowMode(const Vector2& target, float lerp)
{
    cameraPos.x += (target.x - cameraPos.x) * lerp;
    cameraPos.y += (target.y - cameraPos.y) * lerp;
    float halfScreen = SCREEN_WIDTH * 0.5f;

    float minX = leftLimit + halfScreen;
    float maxX = rightLimit - halfScreen;
    if (cameraPos.x < minX) cameraPos.x = minX;
    if (cameraPos.x > maxX) cameraPos.x = maxX;
    view = XMMatrixTranslation(-(cameraPos.x - SCREEN_WIDTH / 2), -(cameraPos.y - SCREEN_HEIGHT / 2), 0.0f);
}
