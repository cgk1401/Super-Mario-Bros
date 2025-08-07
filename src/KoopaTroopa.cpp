#include "../headers/KoopaTroopa.h"
#include "../headers/Collision.h"
#include "../headers/TextureManager.h"
#include "../headers/EffectManager.h"
class Map;

KoopTroopa::KoopTroopa() : Enemy() {
	this->position = { 200, 200 };
	LoadSource();
}

KoopTroopa::KoopTroopa(Vector2 position, MapTheme _theme) {
	this->position = position;
	theme = _theme;
	LoadSource();

	currentState = KoopaState::Walk;
}

KoopTroopa::~KoopTroopa() {
}

void KoopTroopa::LoadSource() {
	texture = Singleton<TextureManager>::getInstance().load(TextureType::ENEMY);

	Animation walk;
	walk.currentframe = 0;
	walk.currenttime = 0;
	walk.durationtime = 0.3f;
	walk.frame.push_back({ 0 + (float)theme * 146, 112, 16, 24 });
	walk.frame.push_back({ 18 + (float)theme * 146, 112, 16, 24 });
	animation[KoopaState::Walk] = walk;

	Animation shell;
	shell.currentframe = 0;
	shell.currenttime = 0;
	shell.durationtime = 0.2;
	shell.frame.push_back({ 72 + (float)theme * 146, 120, 16, 16 });
	animation[KoopaState::Shell] = shell;

	Animation die;
	die.frame.push_back({ 72 + (float)theme * 146, 120, 16, 16 });
	die.durationtime = 0.2;
	animation[KoopaState::Die] = die;
	
}

void KoopTroopa::draw() {
	Rectangle currentframe = animation[currentState].getcurrentframe();
	currentframe.width = direction == Direction::Left ? abs(currentframe.width) : -abs(currentframe.width);

	Rectangle dest = { position.x, position.y, currentframe.width * scale, currentframe.height * scale };
	DrawTexturePro(texture, currentframe, dest, { 0,0 }, 0, WHITE);
}

void KoopTroopa::update(float deltatime) {
	animation[currentState].Update(deltatime);

	if (!onGround) {
		velocity.y += gravity * deltatime;
	}
	else {
		velocity.y = 0;
	}

	if (onGround && velocity.y > 0) {
		velocity.y = 0;
	}

	 
	if(direction == Direction::Right){
		moveRight();
	}
	else if (direction == Direction::Left){
		moveLeft();
	}

	position.y += velocity.y * deltatime;
}

void KoopTroopa::moveLeft() {

	if (currentState == KoopaState::Walk) {
		velocity.x = -walkSpeed * GetFrameTime();
	}
	else if (currentState == KoopaState::Shell) {
		if (!isStationary) velocity.x = -shellSpeed * GetFrameTime();
	}
	position.x += velocity.x;
}

void KoopTroopa::moveRight() {
	if (currentState == KoopaState::Walk) {
		velocity.x = walkSpeed * GetFrameTime();
	}
	else if (currentState == KoopaState::Shell) {
		if(!isStationary) velocity.x = shellSpeed * GetFrameTime();
	}
	position.x += velocity.x;
}

bool KoopTroopa::isDead(){
	return position.y >= GetScreenHeight() + 50 || currentState == KoopaState::Die;
}

void KoopTroopa::Fall() {
	currentState = KoopaState::Shell;
	velocity.y += gravity * GetFrameTime();
	position.y += velocity.y;
}

void KoopTroopa::onDeath(DeathType type, Character* player) {
	switch (type) {
	case DeathType::STOMP:
		if (currentState == KoopaState::Walk) {
			currentState = KoopaState::Shell;
			isStationary = true;
			animation[currentState].reset();
		}
		else if (currentState == KoopaState::Shell) {
			isStationary = false;
			float player_mid = player->getBound().x + player->getBound().width / 2;
			float enemy_mid = getBound().x + getBound().width / 2;
			changeDirection(player_mid >= enemy_mid ? Direction::Left : Direction::Right);
		}
		break;
	case DeathType::FIREBALL_HIT:
	case DeathType::FALLING:
	case DeathType::SHELL_HIT:
		currentState = KoopaState::Die;
		Singleton<EffectManager>::getInstance().koopaDeath(this->position, texture, animation[KoopaState::Die].getcurrentframe());
		break;
	}
}

EnemyType KoopTroopa::getType() const{
	if(this->currentState == KoopaState::Shell)
		return EnemyType::KOOPA_SHELL;
	return EnemyType::KOOPA;
}
Rectangle KoopTroopa::getBound() const {
	Rectangle frame = animation.at(currentState).getcurrentframe();
	float delta = 2.0f; //narrow the width
    return {
        position.x + delta,
        position.y,
        frame.width * scale - delta * 2,
        frame.height * scale
    };
}


void KoopTroopa::onCollideWith(GameObject* object) {
	if(object->getObjectType() == ObjectType::ENEMY){
		Enemy* enemy = dynamic_cast<Enemy*>(object);
		if(!enemy || enemy->isDead()) return;

		if(currentState == KoopaState::Shell){
			enemy->onDeath(DeathType::SHELL_HIT);
			return;
		}
		//else
		if(this->direction == Direction::Right){
			this->direction = Direction::Left;
		}
		else this->direction = Direction::Right;
	}
}
