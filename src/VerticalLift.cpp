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

}

void VerticalLift::update(float deltatime) {
	if (movingDown) {
		this->velocity.y = speedY;
	}
	else if (!movingDown) {
		this->velocity.y = -speedY;
	}
	deltaDis = velocity.y * deltatime;
	position.x += velocity.x * deltatime;
	position.y += velocity.y * deltatime;

	if (position.y <= destinationAbove || position.y >= destinationBelow) {
		movingDown = !movingDown;
	}
}


void VerticalLift::draw() {
	Rectangle currentframe = animations.getcurrentframe();
	Rectangle dest = { position.x, position.y, animations.getcurrentframe().width * scale, animations.getcurrentframe().height * scale };

	DrawTexturePro(texture, currentframe, dest, { 0,0 }, 0, WHITE);
}

Rectangle VerticalLift::getBound() const {
	 Rectangle frame = animations.getcurrentframe();
	
        return {
            position.x,
            position.y,
            frame.width * scale,
            frame.height * scale
        };
}

void VerticalLift::onCollideWith(GameObject* object) {
	if (dynamic_cast<Character*> (object)) {
		Character* character = dynamic_cast<Character*> (object);
		Rectangle boundCharacter = character->getBound();
		float eps = 0.1f;
		float width = boundCharacter.width * (1 - eps * 2);
		float height = 5;
		Rectangle footSensor = {
				boundCharacter.x + boundCharacter.width * eps,
				boundCharacter.y + boundCharacter.height + height,
				width,
				height
		};
		Rectangle bound = getBound();
		character->onGround = false;
		if (CheckCollisionRecs(footSensor, bound)) {
			character->position.y = bound.y - boundCharacter.height;
			character->velocity.y = 0;
			character->onGround = true;
			character->isJumpingUp = false;
			character->standingOnLift = true;
		}

		 else if (CheckCollisionRecs(boundCharacter, bound)) {
			float overlapX = fmin(boundCharacter.x + boundCharacter.width, bound.x + bound.width) - fmax(boundCharacter.x, bound.x);
			float overlapY = fmin(boundCharacter.y + boundCharacter.height, bound.y + bound.height) - fmax(boundCharacter.y, bound.y);
			Direction collideSide = getCollisionDirection(boundCharacter, bound);
			if(collideSide == Direction::Top){
				character->position.y += overlapY;
				character->isJumpingUp = false;
				character->velocity.y = 0;
			}
			else if (collideSide == Direction::Left){
				character->position.x += overlapX;
				character->velocity.x = 0;
			}
			else if(collideSide == Direction::Right){
				character->position.x -= overlapX;
				character->velocity.x = 0;
			}
		}
			//else character->applyGravity = true;
	}
}
