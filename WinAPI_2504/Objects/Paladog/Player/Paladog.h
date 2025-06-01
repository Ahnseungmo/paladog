#pragma once

class Paladog : public RectCollider 
{
private:
	const float SPEED = 400;
	const float SPEEDBUFF = 2.0f;
public:
	Paladog();
	~Paladog();

	void Update();
	void Render();
	void AuraRender();
	void AuraBuff();

	void PunchSkill();

private:
	Quad* paladogTexture;
	Quad* auraTexture;
	RectCollider* auraCollider;
	Punch* punch;
};