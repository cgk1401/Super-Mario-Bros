#include "../headers/Horizontal.h"
#include "../headers/Global.h"
#include "../headers/Singleton.h"
#include "../headers/TextureManager.h"
#include "../headers/Character.h"
#include "../headers/Collision.h"

Horizontal::Horizontal() : Lift() {
	LoadSource();
	SetDestination();
}

Horizontal::Horizontal(Vector2 position) : Lift(position) {
	LoadSource();
	SetDestination();
}

void Horizontal::SetDestination() {
	this->destinationLeft = this->position.x - distance;
	this->destinationRight = this->position.y + distance;
}

void Horizontal::LoadSource() {
	texture = Singleton<TextureManager>::getInstance().load(TextureType::ITEM);

	animations.currentframe = 0;
	animations.currenttime = 0.0f;
	animations.durationtime = 1.0f;
	animations.frame.push_back({ 116, 388, 48,8 });

	bound = { position.x, position.y, animations.getcurrentframe().width * scale, animations.getcurrentframe().height * scale };
}

void Horizontal::Update(float deltatime) {
	if (movingLeft) {
		this->velocity.x = speedX;
	}
	else if (!movingLeft) {
		this->velocity.x = -speedX;
	}

	position.x += velocity.x * deltatime;
	position.y += velocity.y * deltatime;
	bound = { position.x, position.y, animations.getcurrentframe().width * scale, animations.getcurrentframe().height * scale };

	if (position.x <= destinationLeft|| position.x >= destinationRight) {
		movingLeft = !movingLeft;
	}

	Collision::handlePlayer_LiftCollision(Global::character, this);
}

void Horizontal::Draw() {
	Rectangle currentframe = animations.getcurrentframe();
	bound = { position.x, position.y, animations.getcurrentframe().width * scale, animations.getcurrentframe().height * scale };

	DrawTexturePro(texture, currentframe, bound, { 0,0 }, 0, WHITE);
}

Rectangle Horizontal::getBound() {
	return this->bound;
}
