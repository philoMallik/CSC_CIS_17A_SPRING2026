#include "ActionSpace.h"
#include "Player.h"

#include <cstring>

ActionSpace::ActionSpace(int type){
	this->type = type;
	switch (type) {
		case 0:
			std::strcpy(name, "Go");
			break;
		case 1:
			std::strcpy(name, "Chance");
			break;
		case 2:
			std::strcpy(name, "Community Chest");
			break;
		case 3:
			std::strcpy(name, "Income Tax");
			break;
		case 4:
			std::strcpy(name, "Luxury Tax");
			break;
		case 5:
			std::strcpy(name, "Free Parking");
			break;
		case 6:
			std::strcpy(name, "Go To Jail");
			break;
		default:
			std::strcpy(name, "Unknown Action Space");
			break;
	}
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
