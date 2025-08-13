#include "../headers/Bowser.h"
#include "../headers/TextureManager.h"
#include "../headers/SoundManager.h"
#include "../headers/Collision.h"
#include "ItemManager.h"
Bowser::Bowser():Enemy(){
	this->position = { 150, 900 };
	LoadSource();
}

Bowser::Bowser(Vector2 position, MapTheme theme) : Enemy() {
	this->position = position;
	this->theme = theme;
	LoadSource();
}

Bowser::~Bowser() {
	// for (auto it : fireballs) {
	// 	delete it;
	// }
}

void Bowser::LoadSource() {
	texture = Singleton<TextureManager>::getInstance().load(TextureType::ENEMY);

	// OVERWORLD, UNDERGROUND && CASTLE, UNDERWATER
	if (theme == MapTheme::OVERWORLD) {
		animations.frame.push_back({ 0, 208, 32, 32 });
		animations.frame.push_back({ 34, 208, 32, 32 });
		animations.frame.push_back({ 68, 208, 32, 32 });
		animations.frame.push_back({ 102, 208, 32, 32 });
	}
	else if (theme == MapTheme::UNDERGROUND || theme == MapTheme::CASTLE) {
		animations.frame.push_back({ 0 + 146, 208, 32, 32 });
		animations.frame.push_back({ 34 + 146, 208, 32, 32 });
		animations.frame.push_back({ 68 + 146, 208, 32, 32 });
		animations.frame.push_back({ 102 + 146, 208, 32, 32 });
	}
	else if (theme == MapTheme::UNDERWATER) {
		animations.frame.push_back({ 0 + 2 * 146, 208, 32, 32 });
		animations.frame.push_back({ 34 + 2 * 146, 208, 32, 32 });
		animations.frame.push_back({ 68 + 2 * 146, 208, 32, 32 });
		animations.frame.push_back({ 102 + 2 * 146, 208, 32, 32 });
	}
	animations.currentframe = 0;
	animations.currenttime = 0.0f;
	animations.durationtime = 0.3f;
}

void Bowser::draw() {
	Rectangle currentframe = animations.getcurrentframe();
	currentframe.width = direction == Direction::Left ? abs(currentframe.width) : -abs(currentframe.width);
	
	Rectangle dest = { position.x, position.y, currentframe.width * scale, currentframe.height * scale };
	DrawTexturePro(texture, currentframe, dest, { 0,0 }, 0, WHITE);

}

void Bowser::update(float deltatime) {
	animations.Update(deltatime);

	if (direction == Direction::Right) {
		velocity.x = 0;
	}
	else if (direction == Direction::Left) {
		jumpTimer += deltatime;

		if (onGround && jumpTimer >= jumpCooldown) {
			Jump();
			jumpTimer = 0.0f;
		}

		if (movingRight) {
			velocity.x = moveSpeed;
		}
		else {
			velocity.x = -moveSpeed;
		}

		moved += fabs(velocity.x * deltatime);

		if (moved >= moveDistance) {
			movingRight = !movingRight;
			moved = 0.0f;
			if (onGround) {
				Jump();
				jumpTimer = 0.0f;
			}
		}
		CreateFireBalls(deltatime);
	}


	if (!onGround) {
		velocity.y += 800.0f * deltatime;
	}
	else {
		velocity.y = 0;
	}

	position.x += velocity.x * deltatime;
	position.y += velocity.y * deltatime;
}

void Bowser::onDeath(DeathType type, Character* player) {
	animations.durationtime = 0.1f;
	Singleton<SoundManager>::getInstance().play(SoundType::BOWSERFALL);
}

bool Bowser::isDead() {
	return position.y >= screenHeight + 50;
}

EnemyType Bowser::getType() const {
	return EnemyType::BOWSER;
}


Rectangle Bowser::getBound() const {
	Rectangle frame = animations.getcurrentframe();
	float delta = 2.0f; //narrow the width
	return {
		position.x + delta,
		position.y,
		frame.width * scale - delta * 2,
		frame.height * scale
	};
}

void Bowser::onCollideWith(GameObject* object) {
	
}
void Bowser::Jump() {
	velocity.y = jumpForce;
	onGround = false;
}

void Bowser::CreateFireBalls(float deltatime) {
	fireBreathTimer += deltatime;
	
	if (fireBreathTimer >= fireBreathCooldown) {
		fireBreathTimer = 0.0f;
		float posY = Global::character->getPosition().y;
		Singleton<ItemManager>::getInstance().Spawn(ItemType::BOWSER_FIRE_BALL, position, &posY);
		Singleton<SoundManager>::getInstance().play(SoundType::BOWSERFIREBALL);
	}
}