#include "../headers/VerticalLift.h"
#include "../headers/Global.h"
#include "../headers/Singleton.h"
#include "../headers/TextureManager.h"
#include "../headers/Character.h"
#include "../headers/Collision.h"

VerticalLift::VerticalLift() : Lift(){
	LoadSource();
	this->destinationAbove = this->position.y - distance;
	this->destinationBelow = this->position.y + distance;
}

VerticalLift::VerticalLift(Vector2 position) : Lift(position) {
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

void VerticalLift::update(float deltatime) {
	if (movingDown) {
		this->velocity.y = speedY;
	}
	else if (!movingDown) {
		this->velocity.y = -speedY;
	}

	position.x += velocity.x * deltatime;
	position.y += velocity.y * deltatime;
	bound = { position.x, position.y, animations.getcurrentframe().width * scale, animations.getcurrentframe().height * scale };

	if (position.y <= destinationAbove || position.y >= destinationBelow) {
		movingDown = !movingDown;
	}
}


void VerticalLift::draw() {
	Rectangle currentframe = animations.getcurrentframe();
	bound = { position.x, position.y, animations.getcurrentframe().width * scale, animations.getcurrentframe().height * scale };

	DrawTexturePro(texture, currentframe, bound, { 0,0 }, 0, WHITE);
}

Rectangle VerticalLift::getBound() const {
	return this->bound;
}

void VerticalLift::onCollideWith(GameObject* object) {
	if (dynamic_cast<Character*> (object)) {
		Character* character = dynamic_cast<Character*> (object);
		Rectangle boundCharacter = character->getBound();
		float eps = 0.1f;
		float width = boundCharacter.width * (1 - eps * 2);
		float height = 1;
		Rectangle footSensor = {
				boundCharacter.x + boundCharacter.width * eps,
				boundCharacter.y + boundCharacter.height + height,
				width,
				height
		};

		if (CheckCollisionRecs(footSensor, bound)) {
			if (CheckCollisionRecs(footSensor, bound)) {
				character->position.y = bound.y - boundCharacter.height;
				character->velocity.y = 0;
				character->onGround = true;
				character->isJumpingUp = false;
			}
		}

		if (CheckCollisionRecs(boundCharacter, bound)) {
			float overlapX = fmin(boundCharacter.x + boundCharacter.width, bound.x + bound.width) - fmax(boundCharacter.x, bound.x);
			float overlapY = fmin(boundCharacter.y + boundCharacter.height, bound.y + bound.height) - fmax(boundCharacter.y, bound.y);
			if (overlapX > 0 && overlapY > 0) {
				if (overlapY < overlapX) {
					// Vertical Collision
					if (character->velocity.y < 0) {
						character->position.y += overlapY;
						//character->isJumpingUp = false;
						character->velocity.y = 0;
					}
				}
				else {
					// horizontal Collision
					if (character->velocity.x < 0) {
						character->position.x += overlapX;
					}
					else {
						character->position.x -= overlapX;
					}
					character->velocity.x = 0;
				}
			}
		}
	}
}
