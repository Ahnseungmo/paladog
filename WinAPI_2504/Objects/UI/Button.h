#pragma once

class Button : public RectCollider
{
private:


public:
	Button(wstring imagePath, Vector2 size, Vector2 pos);
	~Button();

	void Update();
	void Render();
	void SetOnClick(function<void()> onClickFunc) { onClick = onClickFunc; }
	void Click() {
		if (onClick) onClick();
	}

private:

	Quad* quad;
	function<void()> onClick; 
};