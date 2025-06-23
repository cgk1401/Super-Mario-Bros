#include "../headers/Mario.h"
#include "../headers/Global.h"

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
void Mario::Update(float deltatime, Map* map) {
	animation[currentstate].Update(deltatime);

	// Apply acceleration based on key input
	if (IsKeyDown(KEY_RIGHT)) {
		
		float mut = 1;
		if (velocity.x < 0) {
			mut = 3;
		}
		velocity.x = approach(velocity.x, speed, acceleration * mut * deltatime);
	}

	if (IsKeyDown(KEY_LEFT)) {
		
		float mut = 1;
		if (velocity.x > 0) {
			mut = 3;
		}
		velocity.x = approach(velocity.x, -speed, acceleration * mut * deltatime);
	}

	//FRICTION
	if(!IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT)) {
		// If no keys are pressed, apply friction
		currentstate =Actionstate::IDLE;
		if (onGround) {
			velocity.x = approach(velocity.x, 0, friction * deltatime);
		}
		//add 'friction' animation
		position.x += velocity.x;
		
	}
	 
	else if (IsKeyDown(KEY_LEFT_CONTROL)) {
		velocity.x *= 2;
		velocity.x = clamp(velocity.x, -maxSpeed, maxSpeed);
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

	if (!onGround) {
		velocity.y += gravity * deltatime;
	}
	else {
		velocity.y = 0; 
		isJumpingUp = false;
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
	int texH = 22;
	//IDLE STATE
	Animation idle;
	for (int i = 0; i < 1; i++) {
		idle.frame.push_back(Rectangle{(float)( 92 + i * 18), 29, (float)texW, (float)texH });
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
	run.durationtime = 0.08;
	idle.currenttime = 0;
	animation[Actionstate::Run] = run;

	//JUMPING STATE
	Animation jump;
	
	
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


