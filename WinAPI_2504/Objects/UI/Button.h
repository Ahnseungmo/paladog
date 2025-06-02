#pragma once

class Button : public RectCollider
{
private:


public:
	Button() = default;
	Button(wstring imagePath, Vector2 size, Vector2 pos);
	~Button();

	void Update();
	void Render();
	void SetOnClick(function<void()> onClickFunc) { onClick = onClickFunc; }
	void SetOnClickInt(function<void(int)> onClickInt) { this->onClickInt = onClickInt; }
	void SetIntParameter(int intParameter) { this->intParameter = intParameter; }

	void SetOnClickRInt(function<void(int)> onClickInt) { this->onClickRInt = onClickInt; }
	void SetIntParameterR(int intParameter) { this->intParameterR = intParameter; }

	Quad* GetQuad() { return quad; }

	void Click() {
		if (onClick) onClick();
	}

protected:
	Quad* quad;
	function<void()> onClick;
	function<void(int)> onClickInt;
	function<void(int)> onClickRInt;
	int intParameterR = 0;
	int intParameter = 0;
};