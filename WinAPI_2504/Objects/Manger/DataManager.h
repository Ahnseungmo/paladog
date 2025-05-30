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
	int key;
	Type type;
	string name;

	float baseHp;
	float baseAttack;
	float baseSpeed;
	float baseAttackSpeed;
	float sightRange;
	int attackCount;
	string explane;
};

struct AllyData {
	int key;
	string name;
	int cost;
	float hpPerLevel;
	float attackPerLevel;
	float speedPerLevel;
	float attackSpeedPerLevel;

};

struct EnemyData {
	int key;
	string name;

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

	void LoadCharacterData(const string& fileName);

	void LoadAllyData(const string& fileName);

	void LoadEnemyData(const string& fileName);

	ItemData GetItem(int key) { return itemDatas[key]; }
	int GetItemCount() { return itemDatas.size(); }

	const CharacterData& GetCharacter(int key) const { return characterDatas.at(key); }
	int GetCharacterCount() const { return characterDatas.size(); }

	const EnemyData& GetEnemy(int key) const { return enemyDatas.at(key); }
	int GetEnemyCount() const { return enemyDatas.size(); }

	const AllyData& GetMinion(int key) const { return allyDatas.at(key); }
	const unordered_map<int, AllyData>& GetMinionDatas() const { return allyDatas; }
	int GetMinionCount() const { return allyDatas.size(); }

	BagData& GetBag(int key) { return bagDatas.at(key); }
	unordered_map<int, BagData>& GetBagDatas() { return bagDatas; }
	int GetBagCount() const { return bagDatas.size(); }

	const WeaponData& GetWeapon(int key) const { return weaponDatas.at(key); }
	int GetWeaponCount() const { return weaponDatas.size(); }

	WeaponBagData GetWeaponBag(int key) const { return weaponBagDatas.at(key); }
	int GetWeaponBagCount() const { return weaponBagDatas.size(); }

	vector<int>& GetDeck() { return deck; }



private:
	unordered_map<int, ItemData> itemDatas;


	unordered_map<int, CharacterData> characterDatas;
	unordered_map<int, EnemyData> enemyDatas;
	unordered_map<int, AllyData> allyDatas;
	unordered_map<int, BagData> bagDatas;
	unordered_map<int, WeaponData> weaponDatas;
	unordered_map<int, WeaponBagData> weaponBagDatas;

	vector<int> weapons;
	vector<int> deck;

};