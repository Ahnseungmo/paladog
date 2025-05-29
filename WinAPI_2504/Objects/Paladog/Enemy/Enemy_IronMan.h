#pragma once

class Enemy_IronMan : public Character
{
public:
	Enemy_IronMan();
	~Enemy_IronMan();

private:
	void CreateClips() override;
};