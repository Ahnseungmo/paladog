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

	string name;
	Type type;

	float baseHp;
	float baseAttack;
	float baseSpeed;
	float baseAttackSpeed;
	float sightRange;
	int attackCount;
	string explane;
};

struct AllyData {

	string name;
	int cost;
	float hpPerLevel;
	float attackPerLevel;
	float speedPerLevel;
	float attackSpeedPerLevel;

};

struct EnemyData {
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
	string name;
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

	const CharacterData& GetCharacter(string key) const { return characterDatas.at(key); }
	int GetCharacterCount() const { return characterDatas.size(); }

	const EnemyData& GetEnemy(string key) const { return enemyDatas.at(key); }
	int GetEnemyCount() const { return enemyDatas.size(); }

	const AllyData& GetAlly(string key) const { return allyDatas.at(key); }
	const unordered_map<string, AllyData>& GetAllyDatas() const { return allyDatas; }
	int GetAllyCount() const { return allyDatas.size(); }

	BagData& GetBag(string key) { return bagDatas.at(key); }
	unordered_map<string, BagData>& GetBagDatas() { return bagDatas; }
	int GetBagCount() const { return bagDatas.size(); }

	const WeaponData& GetWeapon(string key) const { return weaponDatas.at(key); }
	int GetWeaponCount() const { return weaponDatas.size(); }

	WeaponBagData GetWeaponBag(string key) const { return weaponBagDatas.at(key); }
	int GetWeaponBagCount() const { return weaponBagDatas.size(); }

	vector<string>& GetDeck() { return deck; }



private:
	unordered_map<int, ItemData> itemDatas;



	unordered_map<string, CharacterData> characterDatas;
	unordered_map<string, EnemyData> enemyDatas;
	unordered_map<string, AllyData> allyDatas;
	unordered_map<string, BagData> bagDatas;

	unordered_map<string, WeaponData> weaponDatas;
	unordered_map<string, WeaponBagData> weaponBagDatas;

	vector<string> weapons;
	vector<string> deck;

};