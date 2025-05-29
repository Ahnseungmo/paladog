#pragma once

class Enemy_Witch : public Character
{
public:
	Enemy_Witch();
	~Enemy_Witch();


private:
	void CreateClips() override;
};