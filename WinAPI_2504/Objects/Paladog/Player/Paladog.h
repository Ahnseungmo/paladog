#pragma once

class Paladog : public Character
{
private:
	const float SPEED = 400;
	const float SPEEDBUFF = 1.5f;
	const float ATTACK_SPEEDBUFF = 1.5f;
	const float LEFT_EDGE = -500.0f;
	const float RIGHT_EDGE = 1280.0f;
public:
	Paladog();
	~Paladog();

	void Update();
	void Render();
	void AuraRender();
	void AuraBuff();
	RectCollider* GetAuraCollider() { return auraCollider; }

	void PunchSkill();
private:
	void CreateClips() override;

private:
	Quad* paladogTexture;
	Quad* auraTexture;
	RectCollider* auraCollider;
	Punch* punch;
};