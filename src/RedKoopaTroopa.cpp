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

}

void RedKoopaTroopa::onDeath(DeathType type, Character* player) {

}

bool RedKoopaTroopa::isDead() {
	return false;
}

void RedKoopaTroopa::moveLeft() {

}

void RedKoopaTroopa::moveRight() {

}

void RedKoopaTroopa::Fall() {

}

EnemyType RedKoopaTroopa::getType() const {
	return EnemyType();
}