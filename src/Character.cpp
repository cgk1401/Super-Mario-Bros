#include "../headers/Character.h"
#include "../headers/Map.h"
#include <iostream>
using namespace std;


Character::Character() : gravity(1500), velocity({ 0, 0 }) {
	scale = 1;
	bound = {};
	onGround = false;
	isJumpingUp = false;
    
}

/*
Character::~Character() {
	//UnloadTexture(texture);
	//animation.clear();
}
*/

Vector2 Character::getPos() {
	return position;
}
