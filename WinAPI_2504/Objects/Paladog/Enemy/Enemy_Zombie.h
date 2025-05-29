#pragma once

class Enemy_Zombie : public Character
{
public:
	Enemy_Zombie();
	~Enemy_Zombie();

private:
	void CreateClips() override;


};