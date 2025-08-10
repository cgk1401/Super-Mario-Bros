#include "../headers/KoopaParatroopa.h"
#include "../headers/Singleton.h"
#include "../headers/TextureManager.h"
#include "../headers/EffectManager.h"

KoopaParatroop::KoopaParatroop() : Enemy() {
	interactWithMap = false;
	this->position = { 150, 300 };
	LoadSource();
	setDistance();
}

KoopaParatroop::KoopaParatroop(Vector2 position, MapTheme theme) : Enemy() {
	interactWithMap = false;
	this->position = position;
	this->theme = theme;
	LoadSource();
	setDistance();
}

KoopaParatroop::~KoopaParatroop(){}

void KoopaParatroop::LoadSource() {
	texture = Singleton<TextureManager>::getInstance().load(TextureType::ENEMY);

	animations.currentframe = 0.0f;
	animations.currenttime = 0.0f;
	animations.durationtime = 0.3f;
	CreateFrame(animations);
}

void KoopaParatroop::setDistance() {
	destinationAbove = this->position.y - distance;
	destinationBelow = this->position.y + distance;
}

void KoopaParatroop::onDeath(DeathType type, Character* player) {
	switch (type)
	{
	case DeathType::FIREBALL_HIT:
		ChangeState(KoopParatroopState::Die);
		break;
	default:
		break;
	}
}

bool KoopaParatroop::isDead() {
	return currentState == KoopParatroopState::Die;
}

void KoopaParatroop::ChangeState(KoopParatroopState state) {
	currentState = state;
	animations.durationtime = 0.0f;
	animations.currentframe = 0.0f;
	
	Animation animationdead;
	animationdead.currentframe = 0;
	animationdead.durationtime = 0.1f;
	animationdead.currenttime = 0.0f;
	CreateFrame(animationdead, KoopParatroopState::Die);

	Singleton<EffectManager>::getInstance().koopaDeath(this->position, texture, animationdead);
}

EnemyType KoopaParatroop::getType() const {
	return EnemyType::KOOPA_PARATROOPA;
}

void KoopaParatroop::draw() {
	Rectangle currentframe = animations.getcurrentframe();
	Rectangle destination = { this->position.x, this->position.y, currentframe.width * scale, currentframe.height * scale };
	DrawTexturePro(texture, currentframe, destination, { 0,0 }, 0, WHITE);
}

void KoopaParatroop::update(float deltatime) {
	animations.Update(deltatime);

	if (movingDown) {
		velocity.y = speedY;
	}
	else if (!movingDown) {
		velocity.y = -speedY;
	}

	position.x += velocity.x * deltatime;
	position.y += velocity.y * deltatime;

	if (position.y >= destinationBelow || position.y <= destinationAbove) {
		movingDown = !movingDown;
	}

}

Rectangle KoopaParatroop::getBound() const {
	Rectangle frame = animations.getcurrentframe();
	float delta = 2.0f; //narrow the width
	return {
		position.x + delta,
		position.y,
		frame.width * scale - delta * 2,
		frame.height * scale
	};
}

void KoopaParatroop::CreateFrame(Animation& animations, KoopParatroopState currentState) {
	float inverse = 1;
	if (currentState == KoopParatroopState::Alive) inverse = 1;
	else inverse = -1;

	if (theme == MapTheme::OVERWORLD) {
		animations.frame.push_back({ 36, 112, inverse* 16, inverse *24 });
		animations.frame.push_back({ 54, 112, inverse * 16, inverse * 24 });
	}
	else if (theme == MapTheme::UNDERGROUND || theme == MapTheme::CASTLE) {
		animations.frame.push_back({ 182, 112, inverse * 16, inverse * 24 });
		animations.frame.push_back({ 200, 112, inverse * 16, inverse * 24 });
	}
	else if (theme == MapTheme::UNDERWATER) {
		animations.frame.push_back({ 328, 112, inverse * 16, inverse * 24 });
		animations.frame.push_back({ 346, 112, inverse * 16, inverse * 24 });
	}
}

void KoopaParatroop::onCollideWith(GameObject* object) {}