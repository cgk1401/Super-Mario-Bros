#include "../headers/PiranhaPlant.h"
#include "../headers/TextureManager.h"
class Map;


PiranhaPlant::PiranhaPlant() : Enemy(){
	interactWithMap = false;
	basePos = { 500,200 };
	this->position = { 500, 200 };
	LoadSource();
	float riseHeight = animation.getcurrentframe().height * scale;
	riseoffset = riseHeight;
}

PiranhaPlant::PiranhaPlant(Vector2 pipeTop, MapTheme _theme) {
	interactWithMap = false;
	basePos = {pipeTop.x + 20, pipeTop.y + 10};
	this->position = basePos;
	theme = _theme;
	LoadSource();

	float riseHeight = animation.getcurrentframe().height * scale;
	riseoffset = riseHeight;
}

PiranhaPlant::PiranhaPlant(Vector2 pipeTop, float riseHeight, MapTheme _theme) {
	interactWithMap = false;
	basePos = {pipeTop.x + 20, pipeTop.y + 10};
	this->position = basePos;
	riseoffset = riseHeight;
	theme = _theme;
	LoadSource();
}
PiranhaPlant::~PiranhaPlant() {
	/*if (texture.id > 0) {
		UnloadTexture(texture);
	}*/
}

void PiranhaPlant::LoadSource() {
	texture = Singleton<TextureManager>::getInstance().load(TextureType::ENEMY);

	animation.currentframe = 0;
	animation.currenttime = 0;
	animation.durationtime = 0.3f;
	animation.frame.push_back({ 0+ (float)theme * 146, 138, 16, 24 });
	animation.frame.push_back({ 18+ (float)theme * 146, 138, 16, 24 });
}

void PiranhaPlant::update(float deltatime) {
	animation.Update(deltatime);

	timer += deltatime;
	float t;
	switch (currentState) {
	case PlantState::Hidden:
		if (timer >= hiddenhold) {
			ChangeState(PlantState::Rising);
		}
		break;
	case PlantState::Rising:
		t = timer / risetime;
		position.y = basePos.y - riseoffset * t;
		if (t >= 1.0f) {
			position.y = basePos.y - riseoffset;
			ChangeState(PlantState::Holding);
		}
		break;
	case PlantState::Holding:
		if (timer >= biteHold) {
			ChangeState(PlantState::Falling);
		}
		break;
	case PlantState::Falling:
		t = timer / risetime;
		position.y = basePos.y - riseoffset * (1.0f - t);
		if (t >= 1.0f) {
			position.y = basePos.y;
			ChangeState(PlantState::Hidden);
		}
		break;

	}
}
void PiranhaPlant::onDeath(DeathType type, Character* player) {
	switch (type)
	{
	case DeathType::FIREBALL_HIT:
		currentState = PlantState::Die;
		break;
	
	default:
		break;
	}
}

bool PiranhaPlant::isDead() {
	return currentState == PlantState::Die;
}

void PiranhaPlant::ChangeState(PlantState newState) {
	currentState = newState;
	timer = 0;
}

void PiranhaPlant::draw() {
	Rectangle currentframe = animation.getcurrentframe();
	Rectangle dest = { position.x, position.y, currentframe.width * scale, currentframe.height * scale };
	DrawTexturePro(texture, currentframe, dest, { 0,0 }, 0, WHITE);
}

EnemyType PiranhaPlant::getType() const {
	return EnemyType::PIRANT_PLANT;
}

void PiranhaPlant::onCollideWith(GameObject* object) {
	
}
Rectangle PiranhaPlant::getBound() const{
	Rectangle frame = animation.getcurrentframe();
	float delta = 2.0f; //narrow the width
    return {
        position.x + delta,
        position.y,
        frame.width * scale - delta * 2,
        frame.height * scale
    };
}