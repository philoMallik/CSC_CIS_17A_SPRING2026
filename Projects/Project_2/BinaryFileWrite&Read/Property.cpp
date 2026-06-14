#include "Property.h"
#include "Player.h"

Property::Property()
	: type(0),
	  price(0),
	  ownerID(nullptr),
	  baseRent(0),
	  isMortgaged(false) {
}

Property::~Property() {
}

int Property::getType() const {
	return type;
}

void Property::setType(int newType) {
	type = newType;
}

int Property::getPrice() const {
	return price;
}

void Property::setPrice(int newPrice) {
	price = newPrice;
}

Player* Property::getOwnerID() const {
	return ownerID;
}

int Property::getMortgageValue() const {
	return mortgageValue;
}

bool Property::getIsMortgaged() const {
	return isMortgaged;
}

int Property::getHouseCost() const {
	return 0;
}

void Property::setMortgageValue(int newMortgageValue) {
	mortgageValue = newMortgageValue;
}

void Property::setBaseRent(int newBaseRent) {
	baseRent = newBaseRent;
}

void Property::setOwner(Player* newOwner) {
	ownerID = newOwner;
}

void Property::toString() const {
	Square::toString();
	cout << "Property Type : " << type << endl;
	cout << "Price         : " << price << endl;
	cout << "Mortgage Value: " << mortgageValue << endl;
	cout << "Base Rent     : " << baseRent << endl;
	cout << "Mortgaged     : " << (isMortgaged ? "Yes" : "No") << endl;
}

void Property::onLand(Player* player) {
	if (player != nullptr) {
		cout << player->getName() << " landed on property " << getName() << "." << endl;
	}
}

int Property::calculateRent(Player* player) const {
	(void)player;
	return baseRent;
}

bool Property::canUpgrade() const {
	return false;
}

void Property::BuildHouse() {
}

void Property::mortgageProperty() {
	isMortgaged = true;
}

void Property::unmortgageProperty() {
	isMortgaged = false;
}