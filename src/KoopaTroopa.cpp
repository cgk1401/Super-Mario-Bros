#include "../headers/KoopaTroopa.h"
#include "../headers/Collision.h"
#include "../headers/TextureManager.h"
#include "../headers/EffectManager.h"
class Map;

KoopTroopa::KoopTroopa() : Enemy() {
	this->position = { 200, 200 };
	LoadSource();
}

KoopTroopa::KoopTroopa(Vector2 position) {
	this->position = position;
	LoadSource();

	currentState = KoopaState::Walk;
}

KoopTroopa::~KoopTroopa() {
}

void KoopTroopa::LoadSource() {
	texture = TextureManager::get().load(TextureType::ENEMY);

	Animation walk;
	walk.currentframe = 0;
	walk.currenttime = 0;
	walk.durationtime = 0.3f;
	walk.frame.push_back({ 0, 112, 16, 24 });
	walk.frame.push_back({ 18, 112, 16, 24 });
	animation[KoopaState::Walk] = walk;

	Animation shell;
	shell.currentframe = 0;
	shell.currenttime = 0;
	shell.durationtime = 0.2;
	shell.frame.push_back({ 72, 120, 16, 16 });
	animation[KoopaState::Shell] = shell;

	Animation die;
	die.frame.push_back({ 72, 120, 16, 16 });
	die.durationtime = 0.2;
	animation[KoopaState::Die] = die;
	
}

void KoopTroopa::Draw() {
	Rectangle currentframe = animation[currentState].getcurrentframe();
	currentframe.width = direction == Direction::Left ? abs(currentframe.width) : -abs(currentframe.width);

	bound = { position.x, position.y, currentframe.width * scale, currentframe.height * scale };
	DrawTexturePro(texture, currentframe, bound, { 0,0 }, 0, WHITE);
}

void KoopTroopa::Update(float deltatime, Map* map) {
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

	position.y += velocity.y * deltatime;

	Rectangle currentFrame = animation[currentState].getcurrentframe();
	bound = { position.x, position.y, currentFrame.width * scale, currentFrame.height * scale };

	Collision::handleEnemyCollision(this, map);
}

void KoopTroopa::moveLeft() {

	if (currentState == KoopaState::Walk) {
		velocity.x = -walkSpeed * GetFrameTime();
	}
	else if (currentState == KoopaState::Shell) {
		if (!isStationary) velocity.x = -shellSpeed * GetFrameTime();
	}
	position.x += velocity.x;
}

void KoopTroopa::moveRight() {
	if (currentState == KoopaState::Walk) {
		velocity.x = walkSpeed * GetFrameTime();
	}
	else if (currentState == KoopaState::Shell) {
		if(!isStationary) velocity.x = shellSpeed * GetFrameTime();
	}
	position.x += velocity.x;
}

bool KoopTroopa::isDead(){
	return position.y >= GetScreenHeight() + 50 || currentState == KoopaState::Die;
}

void KoopTroopa::Fall() {
	currentState = KoopaState::Shell;
	velocity.y += gravity * GetFrameTime();
	position.y += velocity.y;
}

void KoopTroopa::onDeath(DeathType type, Character* source) {
	switch (type) {
	case DeathType::STOMP:
		if (currentState == KoopaState::Walk) {
			currentState = KoopaState::Shell;
			isStationary = true;
			animation[currentState].reset();
		}
		else if (currentState == KoopaState::Shell) {
			isStationary = false;
			float player_mid = source->getBound().x + source->getBound().width / 2;
			float enemy_mid = this->bound.x + this->bound.width / 2;
			changeDirection(player_mid >= enemy_mid ? Direction::Left : Direction::Right);
		}
		break;
	case DeathType::FALLING:
	case DeathType::SHELL_HIT:
		currentState = KoopaState::Die;
		EffectManager::get().koopaDeath(this->position, texture, animation[KoopaState::Die].getcurrentframe());
		break;
	}
}
