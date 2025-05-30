#pragma once
class Allow : public RectCollider
{
public:
	Allow(Vector2 size = Vector2(100, 100));
	~Allow();

	void Update();
	void Render();

	void Move(Vector2 pos);
private:
	Transform* clipTransform;
	MatrixBuffer* worldBuffer;

	CharacterAnimation* animation;
};