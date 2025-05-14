#pragma once

class StorePanel : public Panel
{
public:
	StorePanel();
	~StorePanel();

	void Update() override;
	void Render(HDC hdc) override;

private:
	void CreateGoods();

	//void������ -> � Ÿ������ �� �� ���
	void OnClickGood(void* good);
	

private:
	vector<Good*> goods;
	Good* selectedGood = nullptr;
};