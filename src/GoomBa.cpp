#include "../headers/GoomBa.h"
#include <iostream>
#include "../headers/Collision.h"
#include "../headers/TextureManager.h"

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
	texture = TextureManager::get().load(TextureType::ENEMY);

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

void GoomBa::Update(float deltatime, Map* map) {
	animation[currentState].Update(deltatime);

	if (!onGround) {
		velocity.y += gravity * deltatime;
	}
	else {
		velocity.y = 0;
	}

	if (onGround && velocity.y > 0) {
		velocity.y = 0;
	}

	 
	if(direction == Direction::Right){
		moveRight();
	}
	else if (direction == Direction::Left){
		moveLeft();
	}

	position.y += velocity.y;

	Rectangle currentFrame = animation[currentState].getcurrentframe();
    bound = { position.x, position.y, currentFrame.width * scale, currentFrame.height * scale };

	Collision::handleEnemyCollision(this, map);

}
bool GoomBa::isDead() {
	return currentState == GoomBaState::Die;
}
void GoomBa::moveLeft() {
	velocity.x = -speed * GetFrameTime();
	position.x += velocity.x;
}

void GoomBa::moveRight() {
	velocity.x = speed *  GetFrameTime();
	position.x += velocity.x;
}

void GoomBa::moveUp() {
	if (onGround == true) {
		onGround = false;
		velocity.y = jump;
	}
	velocity.y += gravity * GetFrameTime();
	position.y += velocity.y;
}

void GoomBa::ChangeState(GoomBaState newState) {
	currentState = newState;
	animation[currentState].currentframe = 0;
	animation[currentState].currenttime = 0;
	if (newState == GoomBaState::Die) {
		// tăng position.y
		
	}
}
