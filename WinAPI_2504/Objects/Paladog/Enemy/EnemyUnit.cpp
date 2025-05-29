#include "Framework.h"

EnemyUnit::EnemyUnit()
{
	UnitStat stat;
	stat.maxHp = 80;
	stat.attack = 15;
	stat.moveSpeed = 90;
	stat.attackSpeed = 1.2f;
	stat.attackRange = 70;
	stat.attackCount = 1;

	SetStat(stat);
	SetTeam(TeamType::Enemy);
	CreateClips();
}

EnemyUnit::~EnemyUnit()
{
}

void EnemyUnit::CreateClips()
{
	vector<Frame*> frames;
	frames.push_back(new Frame(L"Resources/Textures/Cookie/cookie0034z03_run01.png"));
	frames.push_back(new Frame(L"Resources/Textures/Cookie/cookie0034z03_run02.png"));
	frames.push_back(new Frame(L"Resources/Textures/Cookie/cookie0034z03_run03.png"));
	frames.push_back(new Frame(L"Resources/Textures/Cookie/cookie0034z03_run04.png"));

	clips.push_back(new Clip(frames, true));

	frames.clear();
	for (int i = 0; i < 7; i++)
	{
		wstring file = L"Resources/Textures/Cookie/cookie0034z03x2_000" + to_wstring(i + 1);
		file += L".png";

		frames.push_back(new Frame(file));
	}

	clips.push_back(new Clip(frames, true));

	LoadClip("Resources/Textures/RedHat/", "RedHat_Dead.xml", false);
}

