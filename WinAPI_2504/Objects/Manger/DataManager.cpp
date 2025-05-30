#include "Framework.h"

DataManager::DataManager()
{
}

DataManager::~DataManager()
{
}

void DataManager::LoadData(const string& fileName)
{
	ifstream file(fileName);
	if (!file.is_open())
	{
		MessageBox(nullptr, L"Failed to open file", L"Error", MB_OK);
		return;
	}

	string line;

	bool isFirstLine = true;

	while (getline(file, line))
	{
		if (isFirstLine)
		{
			isFirstLine = false;
			continue;
		}

		vector<string> data = Utility::SplitString(line, ",");

		ItemData itemData;
		itemData.key = stoi(data[0]);
		itemData.name = data[1];
		itemData.explane = data[2];
		itemData.price = stoi(data[3]);
		itemData.value = stoi(data[4]);
		itemData.type = (ItemData::Type)stoi(data[5]);

		itemDatas[itemData.key] = itemData;
	}
	file.close();
}
void DataManager::LoadCharacterData(const string& fileName)
{
	ifstream file(fileName);
	if (!file.is_open())
	{
		MessageBox(nullptr, L"Failed to open file", L"Error", MB_OK);
		return;
	}

	string line;

	bool isFirstLine = true;

	while (getline(file, line))
	{
		if (isFirstLine)
		{
			isFirstLine = false;
			continue;
		}

		vector<string> data = Utility::SplitString(line, ",");

		CharacterData charData;
		charData.key = stoi(data[0]);
		charData.type = (CharacterData::Type)stoi(data[1]);
		charData.name = data[2];
		charData.baseHp = stof(data[3]);
		charData.baseAttack = stof(data[4]);
		charData.baseSpeed = stof(data[5]);
		charData.baseAttackSpeed = stof(data[6]);
		charData.sightRange = stof(data[7]);
		charData.attackCount = stoi(data[8]);
		charData.explane = data[9];

		characterDatas.insert({ charData.key,charData });
	}
	file.close();
}

void DataManager::LoadAllyData(const string& fileName)
{
	ifstream file(fileName);
	if (!file.is_open())
	{
		MessageBox(nullptr, L"Failed to open file", L"Error", MB_OK);
		return;
	}

	string line;

	bool isFirstLine = true;

	while (getline(file, line))
	{
		if (isFirstLine)
		{
			isFirstLine = false;
			continue;
		}

		vector<string> data = Utility::SplitString(line, ",");

		AllyData allyData;
		allyData.key = stoi(data[0]);
		allyData.name = data[1];
		allyData.cost = stoi(data[2]);
		allyData.hpPerLevel = stof(data[3]);
		allyData.attackPerLevel = stof(data[4]);
		allyData.speedPerLevel = stof(data[5]);
		allyData.attackSpeedPerLevel = stof(data[6]);

		allyDatas.insert({ allyData.key,allyData });

	}
	file.close();
}

void DataManager::LoadEnemyData(const string& fileName)
{
	ifstream file(fileName);
	if (!file.is_open())
	{
		MessageBox(nullptr, L"Failed to open file", L"Error", MB_OK);
		return;
	}

	string line;

	bool isFirstLine = true;

	while (getline(file, line))
	{
		if (isFirstLine)
		{
			isFirstLine = false;
			continue;
		}

		vector<string> data = Utility::SplitString(line, ",");

		EnemyData enemyData;
		enemyData.key = stoi(data[0]);
		enemyData.name = data[1];

		enemyDatas.insert({ enemyData.key,enemyData });

	}
	file.close();
}

