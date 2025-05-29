#pragma once

class Enemy_Warrior : public Character
{
public:
	Enemy_Warrior();
	~Enemy_Warrior();

private:
	void CreateClips() override;
};