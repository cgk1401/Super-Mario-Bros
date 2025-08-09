#include "../headers/BowserFireBall.h"
#include "../headers/TextureManager.h"
#include "../headers/Singleton.h"
#include "../headers/Global.h"
#include "../headers/Collision.h"

BowserFireBall::BowserFireBall() {
	this->velocity = { 0,0 };
	this->position = { 0,0 };
	this->positionDestinationY = 0;
	interactWithMap = false;
	LoadSource();
}

BowserFireBall::BowserFireBall(Vector2 position, float positionDestinationY) {
	this->velocity = { 0,0 };
	this->position = position;
	this->positionDestinationY = positionDestinationY;

	if (position.y <= this->positionDestinationY) isBelow = true;
	else isBelow = false;

	interactWithMap = false;
	LoadSource();
}

BowserFireBall::~BowserFireBall() {
}

void BowserFireBall::update(float deltatime) {
	if (!isActive) return;

	animations.Update(deltatime);
	ActiveStatus();

	velocity.x = -speedX;
	
	if (isBelow) {
		velocity.y = speedY;
	}
	else velocity.y = -speedY;

	if (isBelow) {
		if (position.y >= this->positionDestinationY) {
			velocity.y = 0;
		}
	}
	else {
		if (position.y <= this->positionDestinationY) {
			velocity.y = 0;
		}
	}

	position.x += velocity.x * deltatime;
	position.y += velocity.y * deltatime;
}

void BowserFireBall::LoadSource() {
	texture = Singleton<TextureManager>::getInstance().load(TextureType::ENEMY);

	animations.frame.push_back({ 102, 242, 24, 8 });
	animations.frame.push_back({ 102, 252, 24, 8 });
	animations.currentframe = 0.0f;
	animations.currenttime = 0.0f;
	animations.durationtime = 0.3f;
}

Rectangle BowserFireBall::getBound() const{
	if (!isActive) return { 0, 0, 0, 0 };

	Rectangle currentframe = animations.getcurrentframe();
	return Rectangle{ position.x, position.y, currentframe.width * scale, currentframe.height * scale };
}

void BowserFireBall::draw() {
	Rectangle currentframe = animations.getcurrentframe();
	Rectangle destination = { position.x, position.y, currentframe.width * scale, currentframe.height * scale };
	DrawTexturePro(texture, currentframe, destination, { 0,0 }, 0, WHITE);
}


bool BowserFireBall::getIsActive() {
	return this->isActive;
}

void BowserFireBall::ActiveStatus() {
	Vector2 screenPos = GetWorldToScreen2D(position, Global::camera);
	if (screenPos.x >= screenWidth || screenPos.y >= screenHeight
		|| screenPos.x < -100 || screenPos.y <= 100
		) {
		Deactive();
	}
	/*Collision::handleBowserball_CharacterCollision(this, Global::character);*/
}

void BowserFireBall::Deactive() {
	this->isActive = false;
	collected = true;
}

void BowserFireBall::OnCollected(Character* player) {
	player->onDead();
	Deactive();
	collected = true;
}