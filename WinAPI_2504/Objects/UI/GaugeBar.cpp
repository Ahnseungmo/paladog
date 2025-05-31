#include "Framework.h"

GaugeBar::GaugeBar(float speed, Vector2(barSize), Vector2(barPos), wstring curGaugeImage, wstring maxGaugeImage)
{
	maxGaugeBarTexture = new Quad(maxGaugeImage);
	maxGaugeBarTexture->SetParent(this);
	maxGaugeBarTexture->SetLocalPosition(barPos);
	maxGaugeBarTexture->SetSize(Vector2(barSize));
	maxGaugeBarTexture->UpdateWorld();

	curGaugeBarTexture = new Quad(curGaugeImage);
	curGaugeBarTexture->SetParent(this);
	curGaugeBarTexture->SetLocalPosition(barPos);
	curGaugeBarTexture->SetSize(Vector2(barSize));
	curGaugeBarTexture->UpdateWorld();

	this->barPos = barPos;
	this->barSize = barSize;
	this->speed = speed;
}

GaugeBar::~GaugeBar()
{
	delete maxGaugeBarTexture;
	delete curGaugeBarTexture;
}

void GaugeBar::Update()
{
	if(curGauge <= maxGauge)
		curGauge += speed * DELTA;

	ratio = curGauge / maxGauge;
	curGaugeBarWidth = barSize.x * ratio;
	curGaugeBarTexture->SetSize(Vector2(curGaugeBarWidth, barSize.y));
	float leftEdgeX = barPos.x - (barSize.x / 2);
    float newPosX = leftEdgeX + (curGaugeBarWidth / 2);
    //curGaugeBarTexture->SetLocalPosition(Vector2(newPosX - barSize.x - barPos.x, barSize.y * 3));
	curGaugeBarTexture->SetLocalPosition(newPosX, barPos.y);
    curGaugeBarTexture->UpdateWorld();
}

void GaugeBar::Render()
{
	maxGaugeBarTexture->Render();
	curGaugeBarTexture->Render();
}
