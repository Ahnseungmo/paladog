#pragma once

class Enemy_IronMan : public Character
{
private:
	const float BEAM_TIME = 2.0f;
	const int ATTACK_COUNT = 5;
	const float MOVE_SPEED = 150.0f;
public:
	Enemy_IronMan();
	~Enemy_IronMan();

	void Update() override;
	void Render() override;
	void AttackTarget() override;

private:
	void CreateBeam();
	void CreateClips() override;
	void BeamUpdate();

	void CheckTimer();

	void UpDownMove();
	void IsSpecial();
private:
	bool isSpecial = false;
	int attackCount = 0;
	float timer = 0.0f;

	Quad* beam;
	RectCollider* beamCollider;
};