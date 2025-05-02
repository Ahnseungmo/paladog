#pragma once

#include "Bullet.h"

//���漱��
//class Bullet;

class Player : public Circle
{
private:
	const int SPEED = 10;
	const int BULLET_POOL_SIZE = 50;

public:
	Player();
	~Player();

	void Update();	
	void Render(HDC hdc);

private:
	void Fire();

private:
	//���漱��
	//Bullet* bullet;
	//vector<Bullet*> bullets;
	bool isKeyPressed = false;
};