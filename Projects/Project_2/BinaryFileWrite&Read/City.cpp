#include "City.h"
#include "Player.h"

City::City(int index, const char* name, int type, int price, int mortgageValue, int colourGroup, int houseCost, int rent0, int rent1, int rent2, int rent3, int rent4)
	: Property(){
	this->setIndex(index);
	this->setName(name);
	this->setType(type);
	this->setPrice(price);
	this->setMortgageValue(mortgageValue);
	this->colorGroup = colourGroup;
	houseCount = 0;
	this->houseCost = houseCost;
	numHouses = 0;
	numHouses = 0;
	this->setBaseRent(rent0); // Set base rent for 0 houses
	rent[0] = rent0;
	rent[1] = rent1;
	rent[2] = rent2;
	rent[3] = rent3;
	rent[4] = rent4;
}

City::~City() {
}

int City::getColorGroup() const {
	return colorGroup;
}

int City::getHouseCost() const {
	return houseCost;
}

int City::getNumHouses() const {
	return numHouses;
}
int City::getRent(int numHouses) const {
	if (numHouses < 0 || numHouses > 4) {
		return 0;
	}
	return rent[numHouses];
}

void City::toString() const {
	Property::toString();
	cout << "City Name     : " << getName() << endl;
	cout << "Color Group   : " << colorGroup << endl;
	cout << (this->getOwnerID() == nullptr ? "Unowned" : "Owned by " + string(this->getOwnerID()->getName())) << endl;
	cout << "Price         : " << this->getPrice() << endl;
	cout << "House Cost    : " << houseCost << endl;
	cout << "House Count   : " << numHouses << endl;
	cout << "Mortgage Value: " << this->getMortgageValue() << endl;
	cout << "Rent Table    : ["
		 << rent[0] << ", "
		 << rent[1] << ", "
		 << rent[2] << ", "
		 << rent[3] << ", "
		 << rent[4] << "]" << endl;
}
void City::onLand(Player* player) {
	cout << player->getName() << " landed on city " << getName() << endl;
	if (this->getOwnerID() == nullptr) {
		cout << "The city is unowned. " << player->getName() << " can choose to buy it for $" << this->getPrice() << "." << endl;
		cout << "Do you want to buy " << getName() << "? (y/n): ";
		char choice;
		cin >> choice;
		if (choice == 'y' || choice == 'Y') {
			if (player->getBalance() >= this->getPrice()) {
				player->buyProperty(this);
				cout << player->getName() << " bought " << getName() << " for $" << this->getPrice() << "." << endl;
			} else {
				cout << player->getName() << " does not have enough balance to buy " << getName() << "." << endl;
			}
		} else {
			cout << player->getName() << " chose not to buy " << getName() << "." << endl;
		}
	} else if (this->getOwnerID() != player) {
		cout << "The city is owned by " << this->getOwnerID()->getName() << ". " << player->getName() << " must pay rent." << endl;
		int rentAmount = calculateRent();
		cout << "Rent amount is $" << rentAmount << "." << endl;
		if (player->getBalance() >= rentAmount) {
			player->deductBalance(rentAmount);
			this->getOwnerID()->addBalance(rentAmount);
			cout << player->getName() << " paid $" << rentAmount << " in rent to " << this->getOwnerID()->getName() << "." << endl;
		} else {
			cout << player->getName() << " does not have enough balance to pay rent. " << player->getName() << " is bankrupt!" << endl;		
			player->BankruptcyTransfer(this->getOwnerID()); // Transfer remaining assets to the owner
		}
	} else {
		cout << player->getName() << " owns this city." << endl;
	}
}

void City::buildHouse() {
	if (numHouses < 4) {
		numHouses++;
		houseCount = numHouses;
	}
}

void City::sellHouse() {
	if (numHouses > 0) {
		numHouses--;
		houseCount = numHouses;
	}
}

int City::calculateRent() const {
	if (numHouses < 0 || numHouses > 4) {
		return 0;
	}
	return rent[numHouses];
}

