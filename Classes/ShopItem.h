#ifndef __SHOPITEM__
#define __SHOPITEM__
#include <string>

class ShopItem {
	int exist;
	std::string img3;
	int matureTime;
	int price;
	std::string name;
	int id;
	int experience;
	int value;
	std::string img2;
	std::string img1;
public:
	ShopItem(
		int exist,
		std::string img3,
		int matureTime,
		int price,
		std::string name,
		int id,
		int experience,
		int value,
		std::string img2,
		std::string img1) {

		this->exist = exist;
		this->img3 = img3;
		this->matureTime = matureTime;
		this->price = price;
		this->name = name;
		this->id = id;
		this->experience = experience;
		this->value = value;
		this->img2 = img2;
		this->img1 = img1;
	}
	std::string getImage1() {
		return this->img1;
	}
	std::string getName() {
		return this->name;
	}
};

#endif