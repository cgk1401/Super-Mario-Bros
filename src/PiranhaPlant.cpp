#include "../headers/PiranhaPlant.h"
class Map;


PiranhaPlant::PiranhaPlant() : Enemy(){
	basePos = { 500,200 };
	this->position = { 500, 200 };
	LoadSource();
	float riseHeight = animation.getcurrentframe().height * scale;
	riseoffset = riseHeight;
}

PiranhaPlant::PiranhaPlant(Vector2 pipeTop) {
	basePos = pipeTop;
	this->position = pipeTop;
	LoadSource();

	float riseHeight = animation.getcurrentframe().height * scale;
	riseoffset = riseHeight;
}

PiranhaPlant::PiranhaPlant(Vector2 pipeTop, float riseHeight) {
	basePos = pipeTop;
	riseoffset = riseHeight;
	this->position = pipeTop;
	LoadSource();
}
PiranhaPlant::~PiranhaPlant() {
	if (texture.id > 0) {
		UnloadTexture(texture);
	}
}

void PiranhaPlant::LoadSource() {
	texture = LoadTexture("../assets/Enemy/Enemies_Bosses.png");

	animation.currentframe = 0;
	animation.currenttime = 0;
	animation.durationtime = 0.3f;
	animation.frame.push_back({ 0, 138, 16, 24 });
	animation.frame.push_back({ 18, 138, 16, 24 });
}

void PiranhaPlant::Update(float deltatime, Map* map) {
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

void PiranhaPlant::ChangeState(PlantState newState) {
	currentState = newState;
	timer = 0;
}

void PiranhaPlant::Draw() {
	Rectangle currentframe = animation.getcurrentframe();
	bound = { position.x, position.y, currentframe.width * scale, currentframe.height * scale };
	DrawTexturePro(texture, currentframe, bound, { 0,0 }, 0, WHITE);
}