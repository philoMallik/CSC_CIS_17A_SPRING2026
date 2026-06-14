#include "Square.h"
#include "Player.h"

#include <cstring>

Square::Square() : index(0) {
	std::strcpy(name, "Square");
}

Square::~Square() {
}

int Square::getIndex() const {
	return index;
}

void Square::setIndex(int newIndex) {
	index = newIndex;
}

const char* Square::getName() const {
	return name;
}

void Square::setName(const char* newName) {
	std::strncpy(name, newName, sizeof(name) - 1);
	name[sizeof(name) - 1] = '\0';
}

void Square::toString() const {
	cout << "Square Index: " << index << endl;
	cout << "Square Name : " << name << endl;
}

