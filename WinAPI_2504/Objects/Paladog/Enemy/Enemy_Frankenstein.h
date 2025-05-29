#pragma once

class Enemy_Frankenstein : public Character
{
public:
	Enemy_Frankenstein();
	~Enemy_Frankenstein();

private:
	void CreateClips() override;
};