#include "../headers/Mario.h"
#include "../headers/Global.h"
#include "../headers/Collision.h"

class Map;

Mario::Mario() {
	type = CharacterType::Mario;
	currentAction = ActionState::Idle;
	position = { 100, 300 };
	this->BasePosition = 300;
	currentState = new NormalState(this);
	currentState->SetAnimation(this);
	currentdirection = Direction::Right;
}

Mario::Mario(Vector2 position) {
	type = CharacterType::Mario;
	currentAction = ActionState::Idle;
	this->position = position;
	this->BasePosition = position.y;
	currentState = new NormalState(this);
	currentState->SetAnimation(this);
	currentdirection = Direction::Right;
}

CharacterType Mario::getCharacterType() {
	return CharacterType::Mario;
}

// void Mario::handleInput(float deltatime) {
// 	float mut = 1.0f;
// 	float targetSpeed = 0.0f;
// 	if (IsKeyDown(KEY_LEFT_CONTROL)) {
// 		targetSpeed = maxSpeed;  // Tăng tốc 
// 	}
// 	else {
// 		targetSpeed = speed;     // Bình thường
// 	}

// 	if (IsKeyDown(KEY_RIGHT)) {

// 		if (velocity.x < 0) {
// 			mut = 3;
// 		}
// 		velocity.x = approach(velocity.x, targetSpeed, acceleration * mut * deltatime);
// 	}

// 	if (IsKeyDown(KEY_LEFT)) {

// 		if (velocity.x > 0) {
// 			mut = 3;
// 		}
// 		velocity.x = approach(velocity.x, -targetSpeed, acceleration * mut * deltatime);
// 	}

// 	//FRICTION 
// 	if (!IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT)) {
// 		// If no keys are pressed, apply friction
// 		if (onGround) {
// 			velocity.x = approach(velocity.x, 0, friction * deltatime); 
// 			 currentstate = Actionstate::IDLE;
// 		}
// 		//add 'friction' animation
// 		position.x += velocity.x;
// 	}

// 	const float maxJumpTime = 0.32;

// 	if (IsKeyDown(KEY_SPACE)) {
// 		if (onGround) {
// 			velocity.y = -450;
// 			onGround = false;
// 			isJumpingUp = true;
// 			jumpTimeElapsed = 0.0f;
// 		}
// 		else if (isJumpingUp) {
// 			jumpTimeElapsed += deltatime;

// 			if (jumpTimeElapsed < maxJumpTime) {
// 				velocity.y = -450;
// 			}
// 			else {
// 				velocity.y = -450 * jumpTimeElapsed / maxJumpTime;
// 				isJumpingUp = false;
// 			}
// 		}
// 	}
// 	else {
// 		isJumpingUp = false;
// 	}

// 	inputHandler.HandInput(this);
// }
// void Mario::Update(float deltatime, Map* map) {
// 	animation[currentstate].Update(deltatime);
// 	handleInput(deltatime);

// 	if (!onGround) {
// 		velocity.y += gravity * deltatime;
// 		if(isJumpingUp) currentstate = Actionstate::Jump;
// 	}
// 	else {
// 		velocity.y = 0; 
// 		isJumpingUp = false;
// 	}
// 	if (onGround && velocity.y > 0) {
// 		velocity.y = 0;
// 	}

// 	position.y += velocity.y * deltatime;
	
// 	Rectangle currentFrame =animation[currentstate].getcurrentframe();
//     bound = { position.x, position.y, currentFrame.width * scale, currentFrame.height * scale };

// 	Collision::getInstance()->handlePlayerCollision(this, map);
	
// }

// void Mario::LoadSource() {
// 	texture = LoadTexture("../assets/Mario/Mario & Luigi.png");

// 	int texW = 16;
// 	int texH = 16;
// 	//IDLE STATE
// 	Animation idle;
// 	idle.frame.push_back(Rectangle{ 0, 8, (float)texW, (float)texH });
// 	idle.currentframe = 0;
// 	idle.durationtime = 0.08;
// 	idle.currenttime = 0;
// 	animation[Actionstate::IDLE] = idle;

// 	//RUNNING STATE
// 	Animation run;
// 	for (int i = 0; i < 3; i++) {
// 		run.frame.push_back(Rectangle{ (float)(20 + i * 18), 8, (float)texW, (float)texH });
// 	}
// 	run.currentframe = 0;
// 	run.durationtime = 0.07;
// 	run.currenttime = 0;
// 	animation[Actionstate::Run] = run;

// 	//JUMPING STATE
// 	Animation jump;
// 	jump.frame.push_back(Rectangle{ 96, 8, (float)texW, (float)texH});
// 	jump.currentframe = 0;
// 	jump.durationtime = 0.08;
// 	jump.currenttime = 0;
// 	animation[Actionstate::Jump] = jump;

	
// }

// void Mario::Draw() {
// 	Rectangle currentFrame = animation[currentstate].getcurrentframe();
// 	if (currentDirection == Direction::RIGHT) {
// 		currentFrame.width = abs(currentFrame.width);
// 	}
// 	if (currentDirection == Direction::LEFT) {
// 		currentFrame.width = -abs(currentFrame.width);
// 	}
// 	bound = { position.x, position.y, currentFrame.width * scale, currentFrame.height * scale };

// 	DrawTexturePro(texture, currentFrame, bound, { 0,0 }, 0, WHITE);

// 	//DrawRectangleRec(bound, RED);
// }

// void Mario::MoveLeft() { 
// 	currentstate = Run;
// 	currentDirection = Direction::LEFT;
// 	position.x += velocity.x; 
// }

// void Mario::MoveRight() { 
// 	currentstate = Run;
// 	currentDirection = Direction::RIGHT;
// 	position.x += velocity.x; 
// }


