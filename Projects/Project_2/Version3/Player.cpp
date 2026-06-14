/* 
 * File:    Player.cpp
 * Author:  Philopatair Mallik
 * Date:    00/00/2026
 * Purpose: class implementation file
 */

//System libraries
#include <iostream>
#include <cstring>
using namespace std;

//User libraries
#include "Player.h"
#include "Property.h"
#include "City.h"
#include "Board.h"

// ============ Constructors ============

// Default constructor
Player::Player() {
    strcpy(name, ""); // Initialize name to an empty string
    id = 0;
    token = 0;
    balance = 1500;  // Standard Monopoly starting balance
    position = 0;    // Start at Go
    inJail = false;
    jailTurns = 0;
    hasGetOutOfJailCard = 0;

    numberOfPropertiesOwned = 0; // Initialize number of properties owned to 0
    for (int i = 0; i < 28; i++) {
        propertiesOwned[i] = nullptr; // Initialize each property in the array
    }
    bankrupt = false; // Initialize bankrupt flag to false
}

// Constructor with parameters
Player::Player(const char* playerName, int playerId, int playerToken) {
    strcpy(name, playerName);
    id = playerId;
    token = playerToken;
    balance = 1500;  // Standard Monopoly starting balance
    position = 0;    // Start at Go
    inJail = false;
    jailTurns = 0;
    hasGetOutOfJailCard = 0;

    numberOfPropertiesOwned = 0;
    for (int i = 0; i < 28; i++) {
        propertiesOwned[i] = nullptr; // Initialize each property in the array
    }
    bankrupt = false; // Initialize bankrupt flag to false
}

// ============ Accessors ============

char* Player::getName() const {
    return (char*)name;
}

int Player::getId() const {
    return id;
}

int Player::getToken() const {
    return token;
}

int Player::getBalance() const {
    return balance;
}

int Player::getPosition() const {
    return position;
}

Property* Player::getPropertiesOwned(int index) const {
    if (index >= 0 && index < numberOfPropertiesOwned) {
        return propertiesOwned[index];
    }
    return nullptr; // Return nullptr if the index is out of bounds
}

bool Player::isInJail() const {
    return inJail;
}

int Player::getJailTurns() const {
    return jailTurns;
}

int Player::getHasGetOutOfJailCard() const {
    return hasGetOutOfJailCard;
}

bool Player::isBankrupt() const {
    return bankrupt;
}

// ============ Mutators ============

void Player::setHasGetOutOfJailCard(int count) {
    hasGetOutOfJailCard = count;
}
void Player::setBalance(int newBalance) {
    balance = newBalance;
    if (balance <= 0) {
        this->declareBankruptcy(); // Declare bankruptcy if balance is less than or equal to 0
    } else {
        bankrupt = false;
    }
}

// ============ Operator Overloads ============

void Player::incrementJailTurns() {
    jailTurns++;
}

// ============ Member Functions ============

void Player::toString() const {
    cout << "Player Name: " << name << endl;
    cout << "Player ID: " << id << endl;
    cout << "Player Token: " << token << endl;
    cout << "Balance: $" << balance << endl;
    cout << "Position: " << position << endl;
    cout << "In Jail: " << (inJail ? "Yes" : "No") << endl;
    cout << "Jail Turns: " << jailTurns << endl;
    cout << "Get Out of Jail Cards: " << hasGetOutOfJailCard << endl;
}

void Player::move(int spaces) {
    position += spaces;
    // Handle passing Go (board has 40 squares: 0-39)
    if (position >= 40) {
        position %= 40;
        *this += 200;  // Collect $200 for passing Go
    }
}

void Player::moveTo(int newPosition) {
    if (newPosition >= 40) {
        *this += 200;  // Collect $200 for passing Go
        newPosition %= 40;
    }
    position = newPosition;
}

void Player::goToJail() {
    position = 10;  // Jail is at position 10
    inJail = true;
    jailTurns = 0;
}

void Player::getOutOfJail() {
    inJail = false;
    jailTurns = 0;
}

void Player::useGetOutOfJailCard() {
    if (hasGetOutOfJailCard > 0) {
        hasGetOutOfJailCard--;
        getOutOfJail();
    }
}

void Player::buyProperty(Property* property) {
    if (property != nullptr && balance >= property->getPrice()) {
        balance -= property->getPrice();
        property->setOwner(this);  // Set the owner of the property to this player
        propertiesOwned[numberOfPropertiesOwned] = property;  // Add property to player's owned properties
        numberOfPropertiesOwned++;
    }
}
void Player::receiveProperty(Property* property) {
    if (property != nullptr) {
        property->setOwner(this);  // Set the owner of the property to this player
        propertiesOwned[numberOfPropertiesOwned] = property;  // Add property to player's owned properties
        numberOfPropertiesOwned++;
    }
}

void Player::UpgradeProperty(Board& board) {
    cout << "Here is a list of your properties:" << endl;
    for (int i = 0; i < numberOfPropertiesOwned; i++) {
        cout << i + 1 << ". " << propertiesOwned[i]->getName() << endl;
    }
    cout << "Enter the number of the property you want to upgrade: ";
    int choice;
    cin >> choice;
    if (choice > 0 && choice <= numberOfPropertiesOwned) {
        Property* propertyToUpgrade = propertiesOwned[choice - 1];
        if (propertyToUpgrade->getType() == 1) { // Check if it's a City
            City* citytoUpgrade = static_cast<City*>(propertyToUpgrade); // Cast to City type to access city-specific functions
            //check if city can be upgraded (not already at max level, player has enough balance, etc.)
            if (citytoUpgrade->canUpgrade() && balance >= citytoUpgrade->getHouseCost()) {
                balance -= citytoUpgrade->getHouseCost(); // Deduct upgrade cost from player's balance
                citytoUpgrade->buildHouse(); // Upgrade the property (e.g., add a house or hotel)
                cout << "Property upgraded successfully!" << endl;
            } else {
                cout << "Cannot upgrade this property. Either it's already at max level or you don't have enough balance." << endl;
            }
        } else {
            cout << "Only cities can be upgraded with houses or hotels." << endl;
        }
    } else {
        cout << "Invalid choice. Please try again." << endl;
    }  
}

void Player::mortgageProperty(Board& board) {
    cout << "Here is a list of your properties:" << endl;
    for (int i = 0; i < numberOfPropertiesOwned; i++) {
        cout << i + 1 << ". " << propertiesOwned[i]->getName() << endl;
    }
    cout << "Enter the number of the property you want to mortgage: ";
    int choice;
    cin >> choice;
    if (choice > 0 && choice <= numberOfPropertiesOwned) {
        Property* propertyToMortgage = propertiesOwned[choice - 1];
        if (!propertyToMortgage->getIsMortgaged()) { // Check if the property is not already mortgaged
            if (propertyToMortgage->getType() == 1) { // If it's a City, check if it can be mortgaged (e.g., no houses/hotels on it)
                City* cityToMortgage = static_cast<City*>(propertyToMortgage);
                if (cityToMortgage->getNumHouses() > 0) {
                    cout << "You cannot mortgage this property because it has houses or hotels on it. Please sell the houses/hotels first." << endl;
                    return;
                }
                else {
                    propertyToMortgage->mortgageProperty(); // Mortgage the property
                    balance += propertyToMortgage->getMortgageValue(); // Add mortgage value to player's balance
                    cout << "Property mortgaged successfully!" << endl;
                }
            }
            else {
                propertyToMortgage->mortgageProperty(); // Mortgage the property
                balance += propertyToMortgage->getMortgageValue(); // Add mortgage value to player's balance
                cout << "Property mortgaged successfully!" << endl;
            }
        } else {
            cout << "This property is already mortgaged." << endl;
        }
    } else {
        cout << "Invalid choice. Please try again." << endl;
    }

}

void Player::unmortgageProperty(Board& board) {
    cout << "Here is a list of your mortgaged properties:" << endl;
    int mortgagedCount = 0;
    int indexesOfMortgagedProperties[28]; // To keep track of the indexes of mortgaged properties in the propertiesOwned array
    for (int i = 0; i < numberOfPropertiesOwned; i++) {
        if (propertiesOwned[i]->getIsMortgaged()) {
            cout << mortgagedCount + 1 << ". " << propertiesOwned[i]->getName() << endl;
            indexesOfMortgagedProperties[mortgagedCount] = i;
            mortgagedCount++;
        }
    }
    if (mortgagedCount == 0) {
        cout << "You have no mortgaged properties." << endl;
    }
    else {
        cout << "Enter the number of the property you want to unmortgage: ";
        int choice;
        cin >> choice;
        if (choice > 0 && choice <= mortgagedCount) {
            Property* propertyToUnmortgage = propertiesOwned[indexesOfMortgagedProperties[choice - 1]];
            if (propertyToUnmortgage->getIsMortgaged()) { // Check if the property is currently mortgaged
                int unmortgageCost = propertyToUnmortgage->getMortgageValue() * 1.1; // Calculate unmortgage cost (mortgage value + 10% interest)
                if (balance >= unmortgageCost) {
                    balance -= unmortgageCost; // Deduct unmortgage cost from player's balance
                    propertyToUnmortgage->unmortgageProperty(); // Unmortgage the property
                    cout << "Property unmortgaged successfully!" << endl;
                } else {
                    cout << "You do not have enough balance to unmortgage this property." << endl;
                }
            } else {
                cout << "This property is not currently mortgaged." << endl;
            }
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void Player::tradeProperty(Player* plyr, Board& board) {
    // This function would facilitate trading properties between two players
}

void Player::declareBankruptcy() {
    balance = 0;
    // Clear propertiesOwned - transfer to appropriate owner
    for (int i = 0; i < numberOfPropertiesOwned; i++) {
        propertiesOwned[i]->setOwner(nullptr); // Set owner to nullptr to indicate it's now unowned
        propertiesOwned[i] = nullptr; // Clear the pointer from the player's propertiesOwned array
    }
    numberOfPropertiesOwned = 0; // Reset the number of properties owned
    bankrupt = true; // Check if the player is bankrupt (balance <= 0)
}

Player& Player::operator+=(int amount) {
    balance += amount;
    if (balance <= 0) {
        this->declareBankruptcy(); // Declare bankruptcy if balance is less than or equal to 0
    } else {
        bankrupt = false;
    }
    return *this;
}
Player& Player::operator-=(int amount) {
    balance -= amount;
    if (balance <= 0) {
        this->declareBankruptcy(); // Declare bankruptcy if balance is less than or equal to 0
    } else {
        bankrupt = false;
    }
    return *this;
}

void Player::BankruptcyTransfer(Player* creditor) {
    // Transfer all properties and remaining balance to the creditor player when declaring bankruptcy
    cout << getName() << " is declaring bankruptcy. Transferring assets to " << creditor->getName() << "." << endl;
    for (int i = 0; i < numberOfPropertiesOwned; i++) {
        cout << "Transferring property: " << propertiesOwned[i]->getName() << " to " << creditor->getName() << endl;
        creditor->receiveProperty(propertiesOwned[i]); // Transfer the property to the creditor player
        propertiesOwned[i] = nullptr; // Clear the pointer from the bankrupt player's propertiesOwned array
    }
    numberOfPropertiesOwned = 0; // Reset the number of properties owned for the bankrupt player
    cout << "Transferring remaining balance of $" << balance << " to " << creditor->getName() << endl;
    *creditor += balance; // Transfer any remaining balance to the creditor player
    balance = 0; // Set bankrupt player's balance to 0
    bankrupt = true; // Set bankrupt flag to true for the bankrupt player
}