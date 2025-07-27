#include "../headers/GoomBa.h"
#include <iostream>
#include "../headers/Collision.h"
#include "../headers/TextureManager.h"
#include "../headers/EffectManager.h"

GoomBa::GoomBa() : Enemy(){
	currentState = GoomBaState::Run;
	this->position = { 150, 500 };
	LoadSource();
}

GoomBa::GoomBa(Vector2 position) : Enemy() {
	currentState = GoomBaState::Run;
	this->position = position;
	LoadSource();
}

GoomBa::~GoomBa() {
	//if (texture.id != 0) {
	//	UnloadTexture(texture);
	//}
}

void GoomBa::LoadSource() {
	texture = Singleton<TextureManager>::getInstance().load(TextureType::ENEMY);

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
	animation[GoomBaState::DIE_STOMP] = die;

	animation[GoomBaState::DIE_FALLING].frame = {};

	
}

void GoomBa::Draw() {
	Rectangle currentframe = animation[currentState].getcurrentframe();
	bound = { position.x, position.y, currentframe.width * scale, currentframe.height * scale };
	DrawTexturePro(texture, currentframe, bound, { 0,0 }, 0, WHITE);
}

void GoomBa::Update(float deltatime, Map* map) {
	animation[currentState].Update(deltatime);
	stomp_dead_timer.update(deltatime);

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

	if (map) Collision::handleEnemyCollision(this, map);

}
bool GoomBa::isDead() {
	if (currentState == GoomBaState::DIE_STOMP)
		return stomp_dead_timer.isFinished();

	if (currentState == GoomBaState::DIE_FALLING)
		return true;

	return false;
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
	if (newState == GoomBaState::DIE_FALLING) {
		// tăng position.y
		Singleton<EffectManager>::getInstance().goombaDead(this->position);
	}
	else if (newState == GoomBaState::DIE_STOMP) {
		stomp_dead_timer.start(0.2f);
	}
}

void GoomBa::onDeath(DeathType type, Character* player) {
	  switch (type) {
        case DeathType::STOMP:
            ChangeState(GoomBaState::DIE_STOMP);
            break;
        case DeathType::FALLING:
        case DeathType::SHELL_HIT:
            ChangeState(GoomBaState::DIE_FALLING);
            break;
    }
}

EnemyType GoomBa::getType() const {
	return EnemyType::GOOMBA;
}
