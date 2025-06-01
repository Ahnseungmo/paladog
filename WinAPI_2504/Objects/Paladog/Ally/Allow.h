#pragma once
class Allow : public RectCollider
{
public:
	Allow(Vector2 size = Vector2(50, 50));
	~Allow();

	void Update();
	void Render();

	void Fire(Vector2 startPos, Character* target);
	void Move();

	void SetSpeed(float speed) { this->speed = speed; }
	void SetTarget(Character* target) { this->target = target; }
private:
	float speed = 500.0f;

	Vector2 dir = Vector2::Right();
	Character* target;
	Transform* clipTransform;
	CharacterAnimation* animation;
	MatrixBuffer* worldBuffer;
};