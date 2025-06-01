#pragma once

class Enemy_Boss : public Character
{
private:
	const float PUSH_TIME = 2.0f;
	const float STUN_TIME = 3.0f;
	const float PUSH_SPEED = 200.0f;
	const int SPECIAL_ATTACK_COUNT = 10;
public:
	Enemy_Boss();
	~Enemy_Boss();

	void Render() override;
	void Update() override;

	void PushTarget();

	void SpawnBoss();

	void AttackTarget() override;

private:
	void CreateHorse();
	void CreateClips() override;
	void ChangeTransform();

	void TimerFunc();

	void SpecialAttack();

	//void Skill();
private:
	int attackCount = 0;
	float timer = 0.0f;
	bool timerSwitch = false;
	bool isPush = false;

	CharacterAnimation* walkingHorse;
	Transform* horseTransform;
	Quad* attackHorse;
};