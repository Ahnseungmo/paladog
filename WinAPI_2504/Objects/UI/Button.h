#pragma once

class Button : public RectCollider
{
public:
	Button(wstring imagePath, Vector2 size, Vector2 pos);
	~Button();

	void Update();
	void Render();
	void SetOnClick(function<void()> onClickFunc) { onClick = onClickFunc; }
	Quad* GetQuad() { return quad; }
	void Click() {
		if (onClick) onClick();
	}

private:
	Quad* quad;
	function<void()> onClick;
};