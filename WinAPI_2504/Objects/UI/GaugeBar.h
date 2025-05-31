#pragma once

class GaugeBar : public Transform 
{
//private:
//	const float SPEED = 50.0f;
//	const float SPAWNBAR_WIDTH = 370.0f;
//	const float SPAWNBAR_HEIGHT = 33.0f;
//	const float SPAWNBAR_POSX = 273.0f;
//	const float SPAWNBAR_POSY = 258.0f;

public:
	GaugeBar(float speed, Vector2(barSize), Vector2(barPos), wstring curGaugeImage, wstring maxGaugeImage);
	~GaugeBar();

	void Update();
	void Render();

	float GetMaxGauge() { return maxGauge; }
	void SetMaxGauge(float maxGauge) { this->maxGauge = maxGauge; }
	float GetCurGauge() { return curGauge; }
	void SetCurGauge(float curGauge) { this->curGauge = curGauge; }

private:
	float maxGauge = 200.0f;
	float curGauge = 0.0f;
	float ratio = 0.0f;
	float curGaugeBarWidth = 0.0f;
	float speed = 5.0f;

	Quad* maxGaugeBarTexture;
	Quad* curGaugeBarTexture;

	Vector2 curGaugeBar = Vector2(0, 0);
	Vector2 barSize;
	Vector2 barPos;
};
