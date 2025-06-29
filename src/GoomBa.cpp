#include "../headers/GoomBa.h"
#include <iostream>

GoomBa::GoomBa() : Enemy(){
	this->position = { 150, 500 };
	LoadSource();
}

GoomBa::GoomBa(Vector2 position) : Enemy() {
	this->position = position;
	LoadSource();
}

GoomBa::~GoomBa() {
	if (texture.id != 0) {
		UnloadTexture(texture);
	}
}

void GoomBa::LoadSource() {
	texture = LoadTexture("../assets/Enemy/Enemies_Bosses.png");

	Animation run;
	run.currentframe = 0;
	run.currenttime = 0;
	run.durationtime = 0.3f;
	run.frame.push_back({ 0, 16, 16, 16 });
	run.frame.push_back({ 18, 16, 16, 16 });
	animation[GoomBaState::Run] = run;

	Animation die;
	die.currentframe = 0;
	die.currenttime = 0;
	die.durationtime = 0.3f;
	die.frame.push_back({ 36, 24, 16, 8 });
	animation[GoomBaState::Die] = die;
}

void GoomBa::Draw() {
	Rectangle currentframe = animation[currentState].getcurrentframe();
	bound = { position.x, position.y, currentframe.width * scale, currentframe.height * scale };
	DrawTexturePro(texture, currentframe, bound, { 0,0 }, 0, WHITE);
}

void GoomBa::Update(float deltatime) {
	animation[currentState].Update(deltatime);
}

void GoomBa::moveLeft() {
	position.x -= speed;
}

void GoomBa::moveRight() {
	position.x += speed;
}

void GoomBa::moveUp() {
	if (isGround == true) {
		isGround = false;
		velocity = jump;
	}
	velocity += gravity;
	position.y += velocity;
}

void GoomBa::ChangeState(GoomBaState newState) {
	currentState = newState;
	animation[currentState].currentframe = 0;
	animation[currentState].currenttime = 0;
	if (newState == GoomBaState::Die) {
		// tăng position.y
	}
}
