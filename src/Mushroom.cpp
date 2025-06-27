#include "../headers/Mushrooom.h"

Mushroom::Mushroom(Vector2 v) {
	xPos = v.x;
	yPos = v.y;
	name = "Mushroom";
	texture = LoadTexture("assets/ingame/Mushroom.png");
}
void Mushroom::draw() {
	DrawTexture(texture, xPos, yPos, WHITE);
}
void Mushroom::update() {
	if (isCaught()) {
		yPos -= 2;
		
	}
}
