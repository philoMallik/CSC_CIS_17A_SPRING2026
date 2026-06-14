#include "Railroad.h"
#include "Player.h"

Railroad::Railroad(int index, char name[])
	: Property() {
	this->setIndex(index);
	this->setName(name);
	this->setType(2); // Type 2 for Railroad
	this->setPrice(200); // Standard price for railroads in Monopoly
	this->setMortgageValue(100); // Standard mortgage value for railroads in Monopoly
	rent[0] = 25;  // Rent with 1 railroad owned
	rent[1] = 50;  // Rent with 2 railroads owned
	rent[2] = 100; // Rent with 3 railroads owned
	rent[3] = 200; // Rent with all 4 railroads owned
}

int Railroad::calculateRent() {
	Player* owner = this->getOwnerID();
	if (owner == nullptr) return 0;
	int ownedRailroads = 0;
	for (int i = 0; i < 28; i++) {
		Property* property = owner->getPropertiesOwned() + i;
		if (property != nullptr && property->getType() == 2 && property->getOwnerID() == owner) {
			ownedRailroads++;
		}
	}
	if (ownedRailroads > 0 && ownedRailroads <= 4) return rent[ownedRailroads - 1];
	else return rent[0];
}

void Railroad::toString() const {
	cout << "Railroad Name : " << getName() << endl;
	cout << (this->getOwnerID() == nullptr ? "Unowned" : "Owned by " + string(this->getOwnerID()->getName())) << endl;
	cout << "Price         : " << this->getPrice() << endl;
	cout << "Mortgage Value: " << this->getMortgageValue() << endl;
	cout << "Rent Table    : ["
		 << rent[0] << ", "
		 << rent[1] << ", "
		 << rent[2] << ", "
		 << rent[3] << "]" << endl;
}

void Railroad::onLand(Player* player) {
	if (player != nullptr) {
		cout << player->getName() << " landed on railroad " << getName() << endl;
	} else {
		cout << "A player landed on railroad " << getName() << "." << endl;
	}
	if (this->getOwnerID() == nullptr) {
		cout << "The railroad is unowned. " << player->getName() << " can choose to buy it." << endl;
		cout << "Price: $" << this->getPrice() << endl;
		cout << "Would you like to buy this railroad? (y/n): ";
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
		cout << "The railroad is owned by " << this->getOwnerID()->getName() << ". " << player->getName() << " must pay rent." << endl;
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
		cout << player->getName() << " owns this railroad." << endl;
	}
}
