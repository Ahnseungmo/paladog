#pragma once

struct ItemData
{
	enum Type
	{
		Weapon = 1, Armor, Potion
	};

	int key;
	string name;
	string explane;
	int price;
	int value;
	Type type;
};


struct CharacterData {
	enum Type {
		Minion, Enemy
	};
	enum AttackType {
		Melee, Range, Mage
	};

	int key;
	Type type;
	AttackType attackType;
	string name;

	int baseHp;
	int baseAttack;
	float baseSpeed;
	float baseAttackSpeed;
	Vector2 sightRange;
	Vector2 size;
	string explane;
};

struct MinionData {
	int key;
	string name;
	int cost;
	int hpPerLevel;
	int attackPerLevel;
	float speedPerLevel;
	float attackSpeedPerLevel;

	string explane;
};

struct EnemyData {
	int key;
	string name;
	string explane;
};
struct WeaponData {
	int key;
	string name;
	int cost;
	int level;
	int baseValue;
	int valuePerLevel;
};

struct BagData {
	int key;
	int count;
	int level;

};
struct WeaponBagData {
	int key;
	int count;
	int level;

};



class DataManager : public Singleton<DataManager>
{
	friend class Singleton;

private:
	DataManager();
	~DataManager();

public:
	void LoadData(const string& fileName);

	ItemData GetItem(int key) { return itemDatas[key]; }
	int GetItemCount() { return itemDatas.size(); }

private:
	unordered_map<int, ItemData> itemDatas;


	unordered_map<int, CharacterData> characterDatas;
	unordered_map<int, EnemyData> enemyDatas;
	unordered_map<int, MinionData> minionDatas;
	unordered_map<int, BagData> bagDatas;
	unordered_map<int, WeaponData> weaponDatas;
	unordered_map<int, WeaponBagData> weaponBagDatas;

	vector<int> weapons;
	vector<int> deck;

};