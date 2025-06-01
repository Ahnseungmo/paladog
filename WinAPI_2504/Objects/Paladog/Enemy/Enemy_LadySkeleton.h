#pragma once

struct Weapon
{
	RectCollider* weapon;
	int collisionCount = 0;
	unordered_set< Character*> hitTarget;
};
class Enemy_LadySkeleton : public Character
{
private:
	const int WEAPON_POOLING = 10;
	const float BONE_SPEED = 200.0f;
	const int MAX_COLLISION = 2;
public:
	Enemy_LadySkeleton();
	~Enemy_LadySkeleton();

	void Update() override;
	void AttackTarget() override;
	void Render() override;

private:
	void CreateClips();
	void CreateBones();
	void MoveBone();
	void AttackUnit(Weapon& bone);

private:

	vector<Weapon> bones;
	CharacterAnimation* boneAni;
};