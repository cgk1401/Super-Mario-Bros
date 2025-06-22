#include "../headers/Mario.h"
#include "iostream"
using namespace std;
Mario::Mario() {
	this->position = { 50, 50 };
	speed = 5.0f;
	jumpDuration = 1;
	jumpTimeElapsed = 0;
	scale = 5;
	LoadSource();
}
Mario::Mario(Vector2 position) {
	this->position = position;
	speed = 5.0f;
	LoadSource();
}

void Mario::Update(float deltatime, Map* map) {
	animation[currentstate].Update(deltatime);

	if (IsKeyDown(KEY_LEFT)) {
		velocity.x = -speed;
	}
	else if (IsKeyDown(KEY_RIGHT)) {
		velocity.x = speed;
	}

	const float maxJumpTime = 0.34;

	if (IsKeyDown(KEY_SPACE)) {
		if (onGround) {
			velocity.y = -450;
			onGround = false;
			isJumping = true;
			jumpTimeElapsed = 0.0f;
		}
		else if (isJumping) {
			jumpTimeElapsed += deltatime;

			if (jumpTimeElapsed < maxJumpTime) {
				velocity.y = -450;
			}
			else {
				velocity.y = -450 * jumpTimeElapsed / maxJumpTime;
				isJumping = false;
			}
		}
	}
	else {
		isJumping = false;
	}

	if (!onGround) {
		velocity.y += gravity * deltatime;
	}
	else {
		velocity.y = 0; 
		isJumping = false;
	}
	if (onGround && velocity.y > 0) {
		velocity.y = 0;
	}

	position.y += velocity.y * deltatime;
	

	inputHandler.HandInput(this);
	Character::handleCollision(map);
	
}

void Mario::LoadSource() {
	texture = LoadTexture("../assets/Mario/mario_custom_spritesheet.png");
	
	int texW = 16;
	int texH = 16;
	Animation idle;
	for (int i = 0; i < 1; i++) {
		idle.frame.push_back(Rectangle{(float)( 290 + i * 18), 35, (float)texW, (float)texH });
	}
	idle.currentframe = 0;
	idle.durationtime = 0.08;
	idle.currenttime = 0;
	animation[Actionstate::IDLE] = idle;

	
}

void Mario::Draw() {
	Rectangle currentFrame = animation[currentstate].getcurrentframe();

	bound = { position.x, position.y, currentFrame.width * scale, currentFrame.height * scale };

	DrawTexturePro(texture, currentFrame, bound, { 0,0 }, 0, WHITE);

	//DrawRectangleRec(bound, RED);
}

void Mario::MoveLeft() { position.x += velocity.x; }

void Mario::MoveRight() { position.x += velocity.x; }


