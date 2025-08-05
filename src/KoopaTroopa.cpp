#include "../headers/KoopaTroopa.h"
#include "../headers/Collision.h"
#include "../headers/TextureManager.h"
#include "../headers/EffectManager.h"
class Map;

KoopTroopa::KoopTroopa(EnemyType type) : Enemy() {
	this->position = { 500, 200 };
	enemyType = type;
	LoadSource();

	if (enemyType == EnemyType::KOOPA) currentState = KoopaState::Walk;
	else if (enemyType == EnemyType::REDKOOPA) currentState = KoopaState::RedWalk;
}

KoopTroopa::KoopTroopa(Vector2 position, EnemyType type, MapTheme _theme) {
	this->position = position;
	theme = _theme;
	enemyType = type;
	LoadSource();

	if (enemyType == EnemyType::KOOPA) currentState = KoopaState::Walk;
	else if (enemyType == EnemyType::REDKOOPA) currentState = KoopaState::RedWalk;
}

KoopTroopa::~KoopTroopa() {
}

void KoopTroopa::LoadSource() {
	texture = Singleton<TextureManager>::getInstance().load(TextureType::ENEMY);

	if (enemyType == EnemyType::KOOPA) {
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
	else if (enemyType == EnemyType::REDKOOPA) {
		Animation redwalk;
		redwalk.currentframe = 0;
		redwalk.currenttime = 0.0f;
		redwalk.durationtime = 0.3f;
		redwalk.frame.push_back({ 0, 318, 16, 24 });
		redwalk.frame.push_back({ 18, 318, 16, 24 });
		animation[KoopaState::RedWalk] = redwalk;

		Animation redshell;
		redshell.currentframe = 0;
		redshell.currenttime = 0;
		redshell.durationtime = 0.2;
		redshell.frame.push_back({ 72 , 326, 16, 16 });
		animation[KoopaState::RedShell] = redshell;

		Animation reddie;
		reddie.frame.push_back({ 72 , 326, 16, 16 });
		reddie.durationtime = 0.2;
		animation[KoopaState::RedDie] = reddie;
	}
	
}

void KoopTroopa::Draw() {
	Rectangle currentframe = animation[currentState].getcurrentframe();
	currentframe.width = direction == Direction::Left ? abs(currentframe.width) : -abs(currentframe.width);

	bound = { position.x, position.y, currentframe.width * scale, currentframe.height * scale };
	DrawTexturePro(texture, currentframe, bound, { 0,0 }, 0, WHITE);
}

void KoopTroopa::Update(float deltatime, Map* map) {
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

	Rectangle currentFrame = animation[currentState].getcurrentframe();
	bound = { position.x, position.y, currentFrame.width * scale, currentFrame.height * scale };

	Collision::handleEnemyCollision(this, map);
}

void KoopTroopa::moveLeft() {
	if (currentState == KoopaState::Walk || currentState == KoopaState::RedWalk) {
		velocity.x = -walkSpeed * GetFrameTime();
	}
	else if (currentState == KoopaState::Shell || currentState == KoopaState::RedShell) {
		if (!isStationary) velocity.x = -shellSpeed * GetFrameTime();
	}
	position.x += velocity.x;
}

void KoopTroopa::moveRight() {
	if (currentState == KoopaState::Walk || currentState == KoopaState::RedWalk) {
		velocity.x = walkSpeed * GetFrameTime();
	}
	else if (currentState == KoopaState::Shell || currentState == KoopaState::RedShell) {
		if(!isStationary) velocity.x = shellSpeed * GetFrameTime();
	}
	position.x += velocity.x;
}

bool KoopTroopa::isDead(){
	return position.y >= screenHeight + 50 || currentState == KoopaState::Die || currentState == KoopaState::RedDie;
}

void KoopTroopa::Fall() {
	if (enemyType == EnemyType::KOOPA) {
		currentState = KoopaState::Shell;
	}
	else if (enemyType == EnemyType::REDKOOPA) {
		currentState = KoopaState::RedShell;
	}
	velocity.y += gravity * GetFrameTime();
	position.y += velocity.y;
}

void KoopTroopa::onDeath(DeathType type, Character* source) {
	switch (type) {
	case DeathType::STOMP:
		if (currentState == KoopaState::Walk || currentState == KoopaState::RedWalk) {
			if (enemyType == EnemyType::KOOPA) {
				currentState = KoopaState::Shell;
			}
			else if (enemyType == EnemyType::REDKOOPA) {
				currentState = KoopaState::RedShell;
			}
			isStationary = true;
			animation[currentState].reset();
		}
		else if (currentState == KoopaState::Shell || currentState == KoopaState::RedShell) {
			isStationary = false;
			float player_mid = source->getBound().x + source->getBound().width / 2;
			float enemy_mid = this->bound.x + this->bound.width / 2;
			changeDirection(player_mid >= enemy_mid ? Direction::Left : Direction::Right);
		}
		break;
	case DeathType::FALLING:
	case DeathType::SHELL_HIT:
		if (enemyType == EnemyType::KOOPA) {
			currentState = KoopaState::Die;
			Singleton<EffectManager>::getInstance().koopaDeath(this->position, texture, animation[KoopaState::Die].getcurrentframe());
		}
		else if (enemyType == EnemyType::REDKOOPA) {
			currentState = KoopaState::RedDie;
			Singleton<EffectManager>::getInstance().koopaDeath(this->position, texture, animation[KoopaState::RedDie].getcurrentframe());
		}
		break;
	}
}

EnemyType KoopTroopa::getType() const {
	if (this->currentState == KoopaState::Shell){
		return EnemyType::KOOPA_SHELL;
	}
	if (this->currentState == KoopaState::RedShell) {
		return EnemyType::REDKOOP_SHELL;
	}
	if (enemyType == EnemyType::KOOPA) {
		return EnemyType::KOOPA;
	}
	return EnemyType::REDKOOPA;
}
