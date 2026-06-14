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

const char* Square::getName() const {
	return name;
}

void Square::toString() const {
	cout << "Square Index: " << index << endl;
	cout << "Square Name : " << name << endl;
}

