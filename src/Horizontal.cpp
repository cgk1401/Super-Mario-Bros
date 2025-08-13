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
    this->destinationRight = this->position.x + distance;
}

void Horizontal::LoadSource() {
	texture = Singleton<TextureManager>::getInstance().load(TextureType::ITEM);

	animations.currentframe = 0;
	animations.currenttime = 0.0f;
	animations.durationtime = 1.0f;
	animations.frame.push_back({ 116, 388, 48,8 });

}

void Horizontal::update(float deltatime) {
	if (movingLeft) {
		this->velocity.x = speedX;
	}
	else if (!movingLeft) {
		this->velocity.x = -speedX;
	}

	position.x += velocity.x * deltatime;
	position.y += velocity.y * deltatime;

	if (position.x <= destinationLeft|| position.x >= destinationRight) {
		movingLeft = !movingLeft;
	}
}

void Horizontal::draw() {
	Rectangle currentframe = animations.getcurrentframe();
	Rectangle dest = { position.x, position.y, animations.getcurrentframe().width * scale, animations.getcurrentframe().height * scale };

	DrawTexturePro(texture, currentframe, dest, { 0,0 }, 0, WHITE);
}

Rectangle Horizontal::getBound() const {
	 Rectangle frame = animations.getcurrentframe();
	
        return {
            position.x,
            position.y,
            frame.width * scale,
            frame.height * scale
        };
}

void Horizontal::onCollideWith(GameObject* object) {
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
        Rectangle bound = getBound();
        if (CheckCollisionRecs(footSensor, bound)) {
            character->position.y = bound.y - boundCharacter.height;
            character->position.x += this->velocity.x * 2.0f * GetFrameTime();
            character->velocity.y = 0;
            character->onGround = true;
            character->isJumpingUp = false;
        }

        if (CheckCollisionRecs(boundCharacter, bound)) {
            float overlapX = fmin(boundCharacter.x + boundCharacter.width, bound.x + bound.width) - fmax(boundCharacter.x, bound.x);
            float overlapY = fmin(boundCharacter.y + boundCharacter.height, bound.y + bound.height) - fmax(boundCharacter.y, bound.y);
            if (overlapX > 0 && overlapY > 0) {
                if (overlapY < overlapX) {
                    // Vertical Collision
                    if (character->velocity.y < 0) {
                        character->position.y += overlapY;
                        character->velocity.y = 0;
                    }
                }
                else {
                    // Horizontal Collision
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
