#include "../headers/VerticalLift.h"
#include "../headers/Global.h"
#include "../headers/Singleton.h"
#include "../headers/TextureManager.h"
#include "../headers/Character.h"
#include "../headers/Collision.h"

VerticalLift::VerticalLift() {
	this->position = { 0,0 };
	this->velocity = { 0,0 };
	LoadSource();
	this->destinationAbove = this->position.y - distance;
	this->destinationBelow = this->position.y + distance;
}

VerticalLift::VerticalLift(Vector2 position) {
	this->position = position;
	this->velocity = { 0,0 };
	LoadSource();
	this->destinationAbove = this->position.y - distance;
	this->destinationBelow = this->position.y + distance;

}

void VerticalLift::LoadSource() {
	texture = Singleton<TextureManager>::getInstance().load(TextureType::ITEM);

	animations.currentframe = 0;
	animations.currenttime = 0.0f;
	animations.durationtime = 1.0f;
	animations.frame.push_back({ 116, 388, 48,8 });

	bound = { position.x, position.y, animations.getcurrentframe().width * scale, animations.getcurrentframe().height * scale };
}

void VerticalLift::Update(float deltatime) {
	if (moveingDown) {
		this->velocity.y = speedY;
	}
	else if (!moveingDown) {
		this->velocity.y = -speedY;
	}

	position.x += velocity.x * deltatime;
	position.y += velocity.y * deltatime;
	bound = { position.x, position.y, animations.getcurrentframe().width * scale, animations.getcurrentframe().height * scale };

	if (position.y <= destinationAbove || position.y >= destinationBelow) {
		moveingDown = !moveingDown;
	}
}


void VerticalLift::Draw() {
	Rectangle currentframe = animations.getcurrentframe();
	bound = { position.x, position.y, animations.getcurrentframe().width * scale, animations.getcurrentframe().height * scale };

	DrawTexturePro(texture, currentframe, bound, { 0,0 }, 0, WHITE);
}

Rectangle VerticalLift::getBound() {
	return this->bound;
}