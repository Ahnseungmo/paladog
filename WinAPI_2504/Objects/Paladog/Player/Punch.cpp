#include "Framework.h"

Punch::Punch(Vector2 size) : RectCollider(size)
{
	punchTexture = new Quad(L"Resources/Textures/Paladog/Punch.png");
	punchTexture->SetParent(this);
}

Punch::~Punch()
{
	delete punchTexture;
}

void Punch::Update()
{
	if (!isActive) return;

	if (this->IsActive())
	{
		float punchX = this->GetGlobalPosition().x;
		for (auto enemy : EnemyManager::Get()->ActiveUnits())
		{
			if (!enemy->IsActive()) continue;
			float enemyX = enemy->GetGlobalPosition().x;

			// 펀치가 적을 지나쳤고, 아직 데미지 안 줬으면
			if (punchX > enemyX && this->hitEnemies.count(enemy) == 0)
			{
				enemy->TakeDamage(PUNCH_DAMAGE); // 원하는 데미지 값
				this->hitEnemies.insert(enemy); // 한 번만 맞게 기록
			}
		}
	}

	Translate(Vector2::Right() * SPEED * DELTA);
	punchTexture->UpdateWorld();
	UpdateWorld();
}

void Punch::Render()
{
	if (!isActive) return;

	punchTexture->Render();
	//Collider::Render();
}

void Punch::SetPunch(Vector2 Pos)
{
	if (this->IsActive() && this->GetGlobalPosition().x > SCREEN_WIDTH + 600)
	{
		this->SetActive(false);
		this->SetLocalPosition(Pos);
		hitEnemies.clear();
	}
}
