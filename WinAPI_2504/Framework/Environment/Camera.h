#pragma once

class Camera : public Transform
{
public:
	Camera();
	~Camera();

	void Update();

	void SetTarget(Transform* target) { this->target = target; }
private:
	void FreeMode();
	void FollowMode(const Vector2& target, float lerp);

private:
	float speed = 300.0f;
	Matrix view;

	MatrixBuffer* viewBuffer;

	Transform* target;

	Vector2 cameraPos;
};