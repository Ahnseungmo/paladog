#pragma once

class Paladog : public RectCollider 
{
private:
	const float SPEED = 400;
public:
	Paladog();
	~Paladog();

	void Update();
	void Render();
	void AuraRender();

private:
	Quad* paladogTexture;
	Quad* auraTexture;
	RectCollider* auraCollider;
	Punch* punch;
};