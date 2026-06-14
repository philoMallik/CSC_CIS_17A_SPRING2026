#include "ActionSpace.h"
#include "Player.h"
#include "Square.h"

#include <cstring>

ActionSpace::ActionSpace(int id, const char* name, int type) : Square() {
	this->setIndex(id);
	this->type = type;
	this->setName(name);
	this->name[sizeof(this->name) - 1] = '\0'; // Ensure null-termination
}

int ActionSpace::getType() const {
	return type;
}

const char* ActionSpace::getName() const {
	return name;
}

void ActionSpace::onLand(Player* player) {
	if (player == nullptr) {
		cout << "A player landed on action space " << name << "." << endl;
		return;
	}

	cout << player->getName() << " landed on " << name << ". ";

	switch (type) {
	case 0:
		this->onGo(player);
		break;
	case 1:
		this->onChance(player);
		break;
	case 2:
		this->onCommunityChest(player);
		break;
	case 3:
		this->onIncomeTax(player);
		break;
	case 4:
		this->onLuxuryTax(player);
		break;
	case 5:
		cout << "Free Parking. No action." << endl;
		break;
	case 6:
		this->onGoToJail(player);
		break;
	default:
		cout << "Unknown action space." << endl;
		break;
	}
}

void ActionSpace::onGo(Player* player) {
	cout << "Collect $200 for passing Go." << endl;
	player->addBalance(200);
}

void ActionSpace::onChance(Player* player) {
	cout << "Draw a Chance card." << endl;
	// Implement Chance card logic here
}

void ActionSpace::onCommunityChest(Player* player) {
	cout << "Draw a Community Chest card." << endl;
	// Implement Community Chest card logic here
}

void ActionSpace::onIncomeTax(Player* player) {
	cout << "Pay Income Tax." << endl;
	player->deductBalance(200); // Example amount
}

void ActionSpace::onLuxuryTax(Player* player) {
	cout << "Pay Luxury Tax." << endl;
	player->deductBalance(100); // Example amount
}

void ActionSpace::onGoToJail(Player* player) {
	cout << "Go To Jail." << endl;
	player->goToJail();
}
void ActionSpace::setName(const char* newName) {
	strncpy(this->name, newName, sizeof(this->name) - 1);
	this->name[sizeof(this->name) - 1] = '\0'; // Ensure null-termination
}

void ActionSpace::toString() const {
	cout << "Action Space Name: " << name << endl;
	cout << "Type             : ";
	switch (type) {
	case 0:
		cout << "Go";
		break;
	case 1:
		cout << "Chance";
		break;
	case 2:
		cout << "Community Chest";
		break;
	case 3:
		cout << "Income Tax";
		break;
	case 4:
		cout << "Luxury Tax";
		break;
	case 5:
		cout << "Free Parking";
		break;
	case 6:
		cout << "Go To Jail";
		break;
	default:
		cout << "Unknown";
		break;
	}
	cout << endl;
}