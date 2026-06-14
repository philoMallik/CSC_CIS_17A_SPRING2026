/*
Filename:  ActionSpace.cpp
Author:    Philopatair Mallik
Date:      00/00/2026
Purpose:   class implementation file
*/

//System libraries
#include <iostream>
#include <cstring>
using namespace std;

//User libraries
#include "ActionSpace.h"
#include "Player.h"
#include "Square.h"


ActionSpace::ActionSpace(int id, const char* name, int type) : Square() {
	this->setIndex(id);
	this->type = type;
	this->setName(name);
	this->name[sizeof(this->name) - 1] = '\0'; // Ensure null-termination
}
ActionSpace::ActionSpace(int id, const char* name, int type, Deck<Card>* deck) : Square() {
	this->setIndex(id);
	this->type = type;
	this->setName(name);
	this->name[sizeof(this->name) - 1] = '\0'; // Ensure null-termination
	this->deck = deck;
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
	*player += 200;
}

void ActionSpace::onChance(Player* player) {
	cout << "Draw a Chance card." << endl;
	Card drawnCard = deck->drawCard();
	switch (drawnCard.getActionType()) {
		case 0: // Move to a specific square
			player->moveTo(drawnCard.getValue());
			break;
		case 1: // Move forward/backward a certain number of spaces
			player->move(drawnCard.getValue());
			break;
		case 2: // Pay or receive money
			if (drawnCard.getValue() > 0) {
				cout << "Receive $" << drawnCard.getValue() << "." << endl;
				*player += drawnCard.getValue();
			} else {
				cout << "Pay $" << -drawnCard.getValue() << "." << endl;
				*player -= -drawnCard.getValue();
			}
			break;
		case 3: // Get out of Jail Free
			cout << "You got a Get Out of Jail Free card!" << endl;
			player->setHasGetOutOfJailCard(player->getHasGetOutOfJailCard() + 1);
			break;
		case 4: // Go to Jail
			player->goToJail();
			break;
		case 5: // Advance to Go (Collect $200)
			player->moveTo(0);
			*player += 200;
			break;
		default:
			cout << "Unknown card action." << endl;
			break;
	}
}

void ActionSpace::onCommunityChest(Player* player) {
	cout << "Drawing a Community Chest card." << endl;
	Card drawnCard = deck->drawCard();
	switch (drawnCard.getActionType()) {
		case 0: // Move to a specific square
			player->moveTo(drawnCard.getValue());
			break;
		case 1: // Move forward/backward a certain number of spaces
			player->move(drawnCard.getValue());
			break;
		case 2: // Pay or receive money
			if (drawnCard.getValue() > 0) {
				cout << "Receive $" << drawnCard.getValue() << "." << endl;
				*player += drawnCard.getValue();
			} else {
				cout << "Pay $" << -drawnCard.getValue() << "." << endl;
				*player -= -drawnCard.getValue();
			}
			break;
		case 3: // Get out of Jail Free
			cout << "You got a Get Out of Jail Free card!" << endl;
			player->setHasGetOutOfJailCard(player->getHasGetOutOfJailCard() + 1);
			break;
		case 4: // Go to Jail
			player->goToJail();
			break;
		case 5: // Advance to Go (Collect $200)
			player->moveTo(0);
			*player += 200;
			break;
		default:
			cout << "Unknown card action." << endl;
			break;
	}
}

void ActionSpace::onIncomeTax(Player* player) {
	cout << "Pay Income Tax." << endl;
	*player -= 200; // Example amount
}

void ActionSpace::onLuxuryTax(Player* player) {
	cout << "Pay Luxury Tax." << endl;
	*player -= 100; // Example amount
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