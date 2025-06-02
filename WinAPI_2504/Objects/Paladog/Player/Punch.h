#pragma once

class Punch : public RectCollider 
{
private:
	const float SPEED = 500.0f;
	const float PUNCH_DAMAGE = 50.0f;
public:
	Punch(Vector2 size);
	~Punch();

	void Update();
	void Render();

	void SetPunch(Vector2 Pos);

	void ClearHitEnemies() { hitEnemies.clear(); }

private:
	Quad* punchTexture;
	bool isPunch = false;
	set<Character*> hitEnemies;
};