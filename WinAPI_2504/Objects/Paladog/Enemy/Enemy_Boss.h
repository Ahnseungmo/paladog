#pragma once

class Enemy_Boss : public Character
{
public:
	Enemy_Boss();
	~Enemy_Boss();

	void Render() override;
	void Update() override;

	void PushTarget();

private:
	void CreateHorse();
	void CreateClips() override;
	void ChangeTransform();

	//void Skill();
private:

	CharacterAnimation* walkingHorse;
	Transform* horseTransform;
	Quad* attackHorse;
};