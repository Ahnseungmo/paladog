#pragma once

class Paladog : public Character
{
private:
	const float SPEED = 400;
	const float SPEEDBUFF = 1.5f;
	const float ATTACK_SPEEDBUFF = 1.5f;
public:
	Paladog();
	~Paladog();

	void Update();
	void Render();
	void AuraRender();
	void AuraBuff();

	void PunchSkill();
private:
	void CreateClips() override;

private:
	Quad* paladogTexture;
	Quad* auraTexture;
	RectCollider* auraCollider;
	Punch* punch;
};