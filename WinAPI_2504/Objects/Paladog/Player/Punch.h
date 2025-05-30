#pragma once

class Punch : public RectCollider 
{
private:
	const float SPEED = 500.0f;
public:
	Punch(Vector2 size);
	~Punch();

	void Update();
	void Render();

private:
	Quad* punchTexture;
	bool isPunch = false;
};