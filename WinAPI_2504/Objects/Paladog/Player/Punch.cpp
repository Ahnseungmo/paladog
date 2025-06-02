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

			// ��ġ�� ���� �����ư�, ���� ������ �� ������
			if (punchX > enemyX && this->hitEnemies.count(enemy) == 0)
			{
				enemy->TakeDamage(PUNCH_DAMAGE); // ���ϴ� ������ ��
				this->hitEnemies.insert(enemy); // �� ���� �°� ���
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
