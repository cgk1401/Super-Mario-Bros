#pragma once
#include "raylib.h"
#include <string>
class Item {
public:
	Item() = default;
	Item(Vector2 v);
	virtual ~Item() = default;
	virtual void draw() = 0;
	virtual void update() = 0;
	std::string toString();
	int getXPosition();
	int getYPosition();
	virtual bool isCaught() = 0;
	virtual bool used() = 0;
protected:
	std::string name;
	Texture2D texture;
	int xPos, yPos;
};