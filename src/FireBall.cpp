#include "../headers/FireBall.h"
#include "../headers/Global.h"
#include "../headers/Collision.h"
#include "../headers/EffectManager.h"
#include "../headers/Singleton.h"
#include "Enemy.h"
FireBall::FireBall(Character* character, float positionGround) {
	this->texture = Singleton<TextureManager>::getInstance().load(TextureType::MARIO);
	this->position = { 0,0 };
	this->velocity = { FIREBALL_SPEEDX ,0 };
	this->scale = 3.5f;
	this->isActive = true;
	this->positionGround = positionGround;
	this->currentLifeTime = 0.0f;
	SetAnimation(character);
}


FireBall::FireBall(Vector2 position, Character* character, float positionGround) {
	this->texture = Singleton<TextureManager>::getInstance().load(TextureType::MARIO);
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

void FireBall::update(float deltatime) {
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

void FireBall::draw() {
	if (!isActive) return;
	Rectangle currentframe = animation->getcurrentframe();

	Rectangle destination = { position.x, position.y, currentframe.width * scale, currentframe.height * scale };

	DrawTexturePro(texture, currentframe, destination, { 0,0 }, 0, WHITE);

}

void FireBall::Deactivate() {
	this->isActive = false;
}
void FireBall::explode() {
	Deactivate();
	Singleton<EffectManager>::getInstance().explosionEffect(this->position);
}
void FireBall::ActiveStatus(float deltatime) {
	currentLifeTime += deltatime;

	Vector2 screenPos = GetWorldToScreen2D(position, Global::camera);

	if (screenPos.x > screenWidth || screenPos.x < -100 ||
		screenPos.y > screenHeight || screenPos.y < -100)
	{
		Deactivate();
	}

	// check Collision
	// if (Global::map)
	// 	Collision::handleFireBallCollisionMap(this, Global::map);
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
 void FireBall::onFootCollision(Tile& tile, int row, int col, Map* map, MapTileInstance* tileInstance) {
	velocity.y = BOUNCE_VELOCITY;
}
void FireBall::onGeneralCollision(Direction collideSide, Tile& tile, int row, int col, Map* map, MapTileInstance* tileInstance) {
	explode();
}
void FireBall::onHeadCollision(Tile& tile, int row, int col, Map* map, MapTileInstance* tileInstance) {
	explode();
}

void FireBall::onCollideWith(GameObject* object) {
	if(object->getObjectType() == ObjectType::ENEMY){
		Enemy* enemy = dynamic_cast<Enemy*>(object);
		if(!enemy || enemy->isDead()) return;

		enemy->onDeath(DeathType::FIREBALL_HIT);
		explode();
	}
}
