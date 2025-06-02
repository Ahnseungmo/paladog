#include "Framework.h"

CoolTimeButton::CoolTimeButton(wstring imagePath, Vector2 size, Vector2 pos, float maxCoolTime)
{
	quad = new Quad(imagePath, Vector2(0, 0), Vector2(1.0f, 1.0f));
	SetLocalPosition(pos);
	quad->SetParent(this);
	quad->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	UpdateWorld();
	quad->UpdateWorld();
	quad->GetMaterial()->SetShader(L"ProgressBar.hlsl");
	this->maxCoolTime = maxCoolTime;

	valueBuffer = new FloatValueBuffer();
}

CoolTimeButton::~CoolTimeButton()
{
	delete quad;
	delete valueBuffer;
}

void CoolTimeButton::Update()
{
	Button::Update();
}

void CoolTimeButton::Render()
{
	valueBuffer->SetPS(1);
	Button::Render();
}

void CoolTimeButton::GUIRender()
{
	ImGui::SliderFloat("Value 1", &valueBuffer->GetValue()[0], -PI, PI);
}

void CoolTimeButton::UpdateCoolTime(float cur, float max)
{
	float progress = cur / max;
	float amount = progress * PI * 2;
	valueBuffer->GetValue()[0] = amount;
}
