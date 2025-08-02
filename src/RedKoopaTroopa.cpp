#include "../Headers/RedKoopaTroopa.h"
#include "../headers/KoopaTroopa.h"
#include "../headers/Collision.h"
#include "../headers/TextureManager.h"
#include "../headers/EffectManager.h"
class Map;

RedKoopaTroopa::RedKoopaTroopa() {
	this->position = { 200, 200 };
	LoadSource();
}

RedKoopaTroopa::RedKoopaTroopa(Vector2 position, MapTheme _theme) {
	this->position = position;
	theme = _theme;
	LoadSource();

	currentState = RedKoopaState::Walk;
}

RedKoopaTroopa::~RedKoopaTroopa(){}

void RedKoopaTroopa::LoadSource() {
	texture = Singleton<TextureManager>::getInstance().load(TextureType::ENEMY);

	Animation walk;
	walk.currentframe = 0;
	walk.currenttime = 0.0f;
	walk.durationtime = 0.3f;
	walk.frame.push_back({ 0, 318, 16, 24 });
	walk.frame.push_back({ 18, 318, 16, 24 });
	animations[RedKoopaState::Walk] = walk;

	Animation shell;
	shell.currentframe = 0;
	shell.currenttime = 0;
	shell.durationtime = 0.2;
	shell.frame.push_back({ 72 , 326, 16, 16 });
	animations[RedKoopaState::Shell] = shell;

	Animation die;
	die.frame.push_back({ 72 , 326, 16, 16 });
	die.durationtime = 0.2;
	animations[RedKoopaState::Die] = die;
}

void RedKoopaTroopa::Draw() {
	Rectangle currentframe = animations[currentState].getcurrentframe();
	currentframe.width = direction == Direction::Left ? abs(currentframe.width) : -abs(currentframe.width);
	bound = { position.x, position.y, currentframe.width * scale, currentframe.height * scale };

	DrawTexturePro(texture, currentframe, bound, { 0,0 }, 0, WHITE);
}

void RedKoopaTroopa::Update(float deltatime, Map* map) {
	animations[currentState].Update(deltatime);

	if (!onGround) {
		velocity.y += gravity * deltatime;
	}
	else {
		velocity.y = 0;
	}
	if (onGround && velocity.y > 0) {
		velocity.y = 0;
	}

	if (direction == Direction::Right) {
		moveRight();
	}
	else if (direction == Direction::Left) {
		moveLeft();
	}

	Collision::handleEnemyCollision(this, map);
}

void RedKoopaTroopa::onDeath(DeathType type, Character* source) {
	switch (type) {
	case DeathType::STOMP:
		if (currentState == RedKoopaState::Walk) {
			currentState = RedKoopaState::Shell;
			isStationary = true;
			animations[currentState].reset();
		}
		else if (currentState == RedKoopaState::Shell) {
			isStationary = false;
			float player_mid = source->getBound().x + source->getBound().width / 2;
			float enemy_mid = this->bound.x + this->bound.width / 2;
			changeDirection(player_mid >= enemy_mid ? Direction::Left : Direction::Right);
		}
		break;
	case DeathType::FALLING:
	case DeathType::SHELL_HIT:
		currentState = RedKoopaState::Die;
		Singleton<EffectManager>::getInstance().koopaDeath(this->position, texture, animations[RedKoopaState::Die].getcurrentframe());
		break;
	}
}

bool RedKoopaTroopa::isDead() {
	return position.y >= screenHeight + 50 || currentState == RedKoopaState::Die;
}

void RedKoopaTroopa::moveLeft() {
	if (currentState == RedKoopaState::Walk) {
		velocity.x = -walkSpeed * GetFrameTime();
	}
	else if (currentState == RedKoopaState::Shell) {
		if (!isStationary) {
			velocity.x = -shellSpeed * GetFrameTime();
		}
	}
	position.x += velocity.x;
}

void RedKoopaTroopa::moveRight() {
	if (currentState == RedKoopaState::Walk) {
		velocity.x = walkSpeed * GetFrameTime();
	}
	else if (currentState == RedKoopaState::Shell) {
		if (!isStationary) {
			velocity.x = shellSpeed * GetFrameTime();
		}
	}
	position.x += velocity.x;

}

void RedKoopaTroopa::Fall() {
	currentState == RedKoopaState::Shell;
	velocity.y += gravity * GetFrameTime();
	position.y += velocity.y;
}

EnemyType RedKoopaTroopa::getType() const {
	if (this->currentState == RedKoopaState::Shell)
		return EnemyType::KOOPA_SHELL;
	return EnemyType::KOOPA;
}