#pragma once

enum CastleStatus
{
	Alive, Damage, Broken
};

class Enemy_Castle :public Character
{
public : 
	Enemy_Castle();
	~Enemy_Castle();

	void Update();
	void Render();

private:
	void CreateQuad(CastleStatus status, wstring frontPath, wstring backPath);
	void CheckHP();

	void CreateClips() override {}
	void Animation() override {} // 비워두기
private:
	CastleStatus state = Alive;

private:
	unordered_map<CastleStatus, vector<Quad*>> frames;

};