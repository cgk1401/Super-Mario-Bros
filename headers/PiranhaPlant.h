#pragma once

#include "Enemy.h"

enum class PlantState {
	Hidden,
	Rising,
	Holding,
	Falling
};

class PiranhaPlant : public Enemy {
private:
	Animation animation;
	const float hiddenhold = 7.0f; // thời gian giữa các lần mọc lên
	const float risetime = 0.5f; // thời gian mọc lên và tụt xuống
	float riseoffset; // chiều cao của cây
	Vector2 basePos; // vị trí mép ống
	const float biteHold = 0.7f;
	float timer = 0;
	const float scale = 3.0f;

	PlantState currentState = PlantState::Hidden;
public:
	PiranhaPlant();
	PiranhaPlant(Vector2 pipeTop);
	PiranhaPlant(Vector2 pipeTop, float riseHeight);
	~PiranhaPlant();

	void LoadSource() override;
	void Update(float deltatime, Map* map) override;
	void Draw() override;
	bool isDead() {return false;}

	void ChangeState(PlantState newState);
};