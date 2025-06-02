#pragma once

class Camera : public Transform
{
public:
	Camera();
	~Camera();

	void Update();

	void SetTarget(Transform* target) { this->target = target; }
	void SetLimits(float left, float right);
private:
	void FreeMode();
	void FollowMode(const Vector2& target, float lerp);

private:
	float leftLimit = 0.0f;
	float rightLimit = 0.0f;
	float speed = 300.0f;
	Matrix view;

	MatrixBuffer* viewBuffer;

	Transform* target;

	Vector2 cameraPos;
};