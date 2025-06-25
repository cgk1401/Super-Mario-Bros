#include "../headers/Item.h"

std::string Item::toString() {
	return "Item: " + name + " at (" + std::to_string(xPos) + ", " + std::to_string(yPos) + ")";
	//return name;
}
int Item::getXPosition() {
	return xPos;
}
int Item::getYPosition() {
	return yPos;
}
