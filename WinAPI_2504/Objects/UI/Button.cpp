#include "Framework.h"

Button::Button(wstring imagePath,Vector2 size,Vector2 pos) : RectCollider(size)
{
	quad = new Quad(imagePath, Vector2(0,0), Vector2(1.0f, 1.0f));
	SetLocalPosition(pos);
	quad->SetParent(this);
	quad->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	UpdateWorld();
	quad->UpdateWorld();
}

Button::~Button()
{
	delete quad;
}

void Button::Update()
{
	if (IsPointCollision(mousePos)) {
		if (Input::Get()->IsKeyPress(VK_LBUTTON)) {
			quad->SetColor(0.5f, 0.5f, 0.5f, 1.0f);
		}
		else if (Input::Get()->IsKeyUp(VK_LBUTTON)) {
			quad->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			if (onClick) onClick();
			if (onClickInt) onClickInt(intParameter);	
		}
		else if (Input::Get()->IsKeyPress(VK_RBUTTON)) {
			quad->SetColor(0.5f, 0.5f, 0.5f, 1.0f);
		}
		else if (Input::Get()->IsKeyUp(VK_RBUTTON)) {
			quad->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
//			if (onClick) onClick();
			if (onClickRInt) onClickRInt(intParameterR);
		}
		else {
			quad->SetColor(0.8f, 0.8f, 0.8f, 1.0f);
		}


	}
	else {
		quad->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
	quad->UpdateWorld();
	RectCollider::UpdateWorld();
}

void Button::Render()
{
	quad->Render();
	Collider::Render();
}
