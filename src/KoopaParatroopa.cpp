#include "../headers/KoopaParatroopa.h"
#include "../headers/Singleton.h"
#include "../headers/TextureManager.h"

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

	if (theme == MapTheme::OVERWORLD) {
		animations.frame.push_back({ 36, 112, 16, 24 });
		animations.frame.push_back({ 54, 112, 16, 24 });
	}
	else if (theme == MapTheme::UNDERGROUND || theme == MapTheme::CASTLE) {
		animations.frame.push_back({ 182, 112, 16, 24 });
		animations.frame.push_back({ 200, 112, 16, 24 });
	}
	else if (theme == MapTheme::UNDERWATER) {
		animations.frame.push_back({ 328, 112, 16, 24 });
		animations.frame.push_back({ 346, 112, 16, 24 });
	}
}

void KoopaParatroop::setDistance() {
	destinationAbove = this->position.y - distance;
	destionationBelow = this->position.y + distance;
}

void KoopaParatroop::onDeath(DeathType type, Character* player) {

}

bool KoopaParatroop::isDead() {
	return false;
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
}

Rectangle KoopaParatroop::getBound() const
{
	return Rectangle();
}

void KoopaParatroop::onCollideWith(GameObject* object)
{
}
