#include "../headers/Item.h"

Item::Item(Vector2 v) {
	xPos = static_cast<int>(v.x);
	yPos = static_cast<int>(v.y);
	texture = LoadTexture("../assets/ingame/Flower.h");
}
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
