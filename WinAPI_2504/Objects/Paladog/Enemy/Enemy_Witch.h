#pragma once

class Enemy_Witch : public Character
{
private:
	const int SPECIAL_COUNT = 10;
	const int ADD_HP = 100;
public:
	Enemy_Witch();
	~Enemy_Witch();


	void AttackTarget() override;
private:
	void CreateClips() override;

	void SpecialAttack();

private:
	int specialAttackCount = 0;
};