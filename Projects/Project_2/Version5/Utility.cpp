/*
Filename:  Utility.cpp
Author:    Philopatair Mallik
Date:      00/00/2026
Purpose:   class implementation file
*/

//System libraries

//User libraries
#include "Utility.h"
#include "Player.h"

Utility::Utility(int index, const char* name) : Property() {
	this->setIndex(index);
	this->setName(name);
	this->setType(3); // Type 3 for Utility
	this->setPrice(200); // Standard price for utilities in Monopoly
	this->setMortgageValue(75); // Standard mortgage value for utilities in Monopoly
	rentMultiplier[0] = 4;
	rentMultiplier[1] = 10;
}

int Utility::getRentMultiplier(int index) const {
	if (index < 0 || index > 1) {
		return 0;
	}
	return rentMultiplier[index];
}

int Utility::calculateRent(Player* player, int diceRoll) {
	if (player == nullptr || diceRoll < 0) {
		return 0;
	}
	int ownedUtilities = 0;
	for (int i = 0; i < 28; i++) {
		Property* property = player->getPropertiesOwned(i);
		if (property != nullptr && property->getType() == 3 && property->getOwnerID() == player) {
			ownedUtilities++;
		}
	}
	return ownedUtilities > 0 ? diceRoll * rentMultiplier[ownedUtilities - 1] : 0;
}

void Utility::toString() const {
	cout << "Utility Name  : " << getName() << endl;
	cout << (this->getOwnerID() == nullptr ? "Unowned" : "Owned by " + string(this->getOwnerID()->getName())) << endl;
	cout << "Price         : " << this->getPrice() << endl;
	cout << "Mortgage Value: " << this->getMortgageValue() << endl;
	cout << "Rent Multipliers: ["
		 << rentMultiplier[0] << ", "
		 << rentMultiplier[1] << "]" << endl;
}

void Utility::onLand(Player* player, int diceRoll) {
	if (player != nullptr) {
		cout << player->getName() << " landed on utility " << getName() << "." << endl;
	} else {
		cout << "A player landed on utility " << getName() << "." << endl;
	}
	if (this->getOwnerID() == nullptr) {
		cout << "The utility is unowned. " << player->getName() << " can choose to buy it." << endl;
		cout << "Price: $" << this->getPrice() << endl;
		cout << "Would you like to buy this utility? (y/n): ";
		char choice;
		cin >> choice;
		if (choice == 'y' || choice == 'Y') {
			if (player->getBalance() >= this->getPrice()) {
				player->buyProperty(this);
				cout << player->getName() << " bought " << getName() << " for $" << this->getPrice() << "." << endl;
			} else {
				cout << player->getName() << " does not have enough balance to buy " << getName() << "." << endl;
			}
		}
	} else if (this->getOwnerID() != player) {
		cout << "The utility is owned by " << this->getOwnerID()->getName() << ". " << player->getName() << " must pay rent." << endl;
		int rentAmount = calculateRent(player, diceRoll);
		cout << "Rent amount is $" << rentAmount << "." << endl;
		if (player->getBalance() >= rentAmount) {
			*player -= rentAmount;
			*this->getOwnerID() += rentAmount;
			cout << player->getName() << " paid $" << rentAmount << " in rent to " << this->getOwnerID()->getName() << "." << endl;
		} else {
			cout << player->getName() << " does not have enough balance to pay rent. " << player->getName() << " is bankrupt!" << endl;		
			player->BankruptcyTransfer(this->getOwnerID()); // Transfer remaining assets to the owner
		}
	} else {
		cout << player->getName() << " owns this utility." << endl;
	}
}
