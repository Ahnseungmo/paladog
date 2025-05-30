#pragma once

class Chest : public RectCollider
{
private:
	enum ActionState
	{
		Idle, Open
	};

public:
	Chest();
	~Chest();

	void Update();
	void ChestOpen();
	void ChestIdle();
	void Render();
	void Edit();

private:
	void CreateClips();
	void LoadClip(string path, string file, bool isLoop, float speed = 1.0f);

private:
	ActionState curState = Idle;

	Transform* clipTransform;
	MatrixBuffer* worldBuffer;

	Clip* clip;	
};