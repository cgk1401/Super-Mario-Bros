#include "../headers/FireBall.h"
#include "../headers/Global.h"
#include "../headers/Collision.h"

FireBall::FireBall(Character* character, float positionGround) {
	this->position = { 0,0 };
	this->velocity = { FIREBALL_SPEEDX ,0 };
	this->scale = 3.5f;
	this->isActive = true;
	this->positionGround = positionGround;
	this->currentLifeTime = 0.0f;
	SetAnimation(character);
}


FireBall::FireBall(Vector2 position, Character* character, float positionGround) {
	this->position = position;
	this->velocity = { FIREBALL_SPEEDX ,0 };
	this->scale = 3.5f;
	this->isActive = true;
	this->positionGround = positionGround;
	this->currentLifeTime = 0.0f;
	SetAnimation(character);
}

FireBall::~FireBall() {
	if (animation) {
		animation->frame.clear();
		delete animation;
		animation = nullptr;
	}
}

void FireBall::SetAnimation(Character* character) {
	animation = new Animation();
	animation->durationtime = 0.1f;
	animation->frame.push_back({ 172, 185, 8, 8 });
	animation->frame.push_back({ 182, 185, 8, 8 });
	animation->frame.push_back({ 192, 185, 8, 8 });
	animation->frame.push_back({ 202, 185, 8, 8 });
}

void FireBall::SetVelocity(Vector2 velocity) {
	this->velocity = velocity;
}

void FireBall::Update(float deltatime) {
	if (!isActive) return;

	animation->Update(deltatime);


	velocity.y += FIREBALL_SPEEDY * deltatime;

	// if (position.y + animation->getcurrentframe().height * scale >= positionGround) {
	// 	position.y = positionGround - animation->getcurrentframe().height * scale;
	// 	velocity.y = BOUNCE_VELOCITY * 1.2;
	// }
	ActiveStatus(deltatime);
	
	position.x += velocity.x * deltatime;
	position.y += velocity.y * deltatime;
}

void FireBall::Draw(Character* character) {
	if (!isActive) return;
	Rectangle currentframe = animation->getcurrentframe();

	Rectangle destination = { position.x, position.y, currentframe.width * scale, currentframe.height * scale };

	DrawTexturePro(character->texture, currentframe, destination, { 0,0 }, 0, WHITE);

}

void FireBall::Deactivate() {
	this->isActive = false;
}

void FireBall::ActiveStatus(float deltatime) {
	currentLifeTime += deltatime;
	// if (currentLifeTime >= FIREBALL_LIFETIME) {
	// 	Deactivate();
	// }
	Vector2 _pos = GetWorldToScreen2D(position, Global::camera);
	
	if(_pos.x > screenWidth || _pos.x < -50 || _pos.y > screenHeight || _pos.y < -50)
		Deactivate();

	// checkcollision .....
	if(Global::map)
		Collision::handleFireBallCollisionMap(this, Global::map);
}


Rectangle FireBall::getBound() const {
	Rectangle frame = animation->getcurrentframe();

	return {
		position.x,
		position.y,
		frame.width * scale,
		frame.height * scale
	};
}
