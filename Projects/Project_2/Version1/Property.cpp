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

int Property::getPrice() const {
	return price;
}

Player* Property::getOwnerID() const {
	return ownerID;
}

void Property::setOwner(Player* newOwner) {
	ownerID = newOwner;
}

void Property::mortgageProperty() {
	isMortgaged = true;
}

void Property::unmortgageProperty() {
	isMortgaged = false;
}