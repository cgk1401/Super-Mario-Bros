#include "../headers/Mario.h"
#include "../headers/Global.h"
#include "../headers/Collision.h"
class Map;

Mario::Mario() {
	LoadSource();
	this->position = { 50, 50 };
	jumpDuration = 1;
	jumpTimeElapsed = 0;
	scale = 64 / 16;
	currentDirection = Direction::RIGHT;
}

Mario::Mario(Vector2 position) {
	this->position = position;
	LoadSource();
}

float clamp(float value, float minvalue, float maxvalue) {
	if (value > maxvalue) return maxvalue;
	else if (value < minvalue) return minvalue;
	return value;
}
float approach(float current, float target, float increase) {
	if (current < target) {
		return min(current + increase, target);
	}
	return max(current - increase, target);
}

void Mario::handleInput(float deltatime) {
	float mut = 1.0f;
	float targetSpeed = 0.0f;
	if (IsKeyDown(KEY_LEFT_CONTROL)) {
		targetSpeed = maxSpeed;  // Tăng tốc 
	}
	else {
		targetSpeed = speed;     // Bình thường
	}

	if (IsKeyDown(KEY_RIGHT)) {

		if (velocity.x < 0) {
			mut = 3;
		}
		velocity.x = approach(velocity.x, targetSpeed, acceleration * mut * deltatime);
	}

	if (IsKeyDown(KEY_LEFT)) {

		if (velocity.x > 0) {
			mut = 3;
		}
		velocity.x = approach(velocity.x, -targetSpeed, acceleration * mut * deltatime);
	}

	//FRICTION 
	if (!IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT)) {
		// If no keys are pressed, apply friction
		if (onGround) {
			velocity.x = approach(velocity.x, 0, friction * deltatime); 
			 currentstate = Actionstate::IDLE;
		}
		//add 'friction' animation
		position.x += velocity.x;
	}

	const float maxJumpTime = 0.32;

	if (IsKeyDown(KEY_SPACE)) {
		if (onGround) {
			velocity.y = -450;
			onGround = false;
			isJumpingUp = true;
			jumpTimeElapsed = 0.0f;
		}
		else if (isJumpingUp) {
			jumpTimeElapsed += deltatime;

			if (jumpTimeElapsed < maxJumpTime) {
				velocity.y = -450;
			}
			else {
				velocity.y = -450 * jumpTimeElapsed / maxJumpTime;
				isJumpingUp = false;
			}
		}
	}
	else {
		isJumpingUp = false;
	}

	inputHandler.HandInput(this);
}
void Mario::Update(float deltatime, Map* map) {
	animation[currentstate].Update(deltatime);
	handleInput(deltatime);

	

	if (!onGround) {
		velocity.y += gravity * deltatime;
		if(isJumpingUp) currentstate = Actionstate::Jump;
	}
	else {
		velocity.y = 0; 
		isJumpingUp = false;
	}
	if (onGround && velocity.y > 0) {
		velocity.y = 0;
	}

	position.y += velocity.y * deltatime;
	
	Collision::getInstance()->handlePlayerCollision(this, map);
	
}

void Mario::LoadSource() {
	texture = LoadTexture("../assets/Mario/mario_custom_spritesheet.png");

	int texW = 16;
	int texH = 22;
	//IDLE STATE
	Animation idle;
	for (int i = 0; i < 1; i++) {
		idle.frame.push_back(Rectangle{ (float)(92 + i * 18), 29, (float)texW, (float)texH });
	}
	idle.currentframe = 0;
	idle.durationtime = 0.08;
	idle.currenttime = 0;
	animation[Actionstate::IDLE] = idle;

	//RUNNING STATE
	Animation run;
	for (int i = 1; i <= 6; i++) {
		run.frame.push_back(Rectangle{ (float)(92 + i * 18), 29, (float)texW, (float)texH });
	}
	run.currentframe = 0;
	run.durationtime = 0.07;
	run.currenttime = 0;
	animation[Actionstate::Run] = run;

	//JUMPING STATE
	Animation jump;
	jump.frame.push_back(Rectangle{ (float)(92 + 7 * 18 ), 29, (float)texW, (float)texH});
	jump.currentframe = 0;
	jump.durationtime = 0.08;
	jump.currenttime = 0;
	animation[Actionstate::Jump] = jump;

	
}

void Mario::Draw() {
	Rectangle currentFrame = animation[currentstate].getcurrentframe();
	if (currentDirection == Direction::RIGHT) {
		currentFrame.width = abs(currentFrame.width);
	}
	if (currentDirection == Direction::LEFT) {
		currentFrame.width = -abs(currentFrame.width);
	}
	bound = { position.x, position.y, currentFrame.width * scale, currentFrame.height * scale };

	DrawTexturePro(texture, currentFrame, bound, { 0,0 }, 0, WHITE);

	//DrawRectangleRec(bound, RED);
}

void Mario::MoveLeft() { 
	currentstate = Run;
	currentDirection = Direction::LEFT;
	position.x += velocity.x; 
}

void Mario::MoveRight() { 
	currentstate = Run;
	currentDirection = Direction::RIGHT;
	position.x += velocity.x; 
}


