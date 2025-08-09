#pragma once

#include "Enemy.h"

enum class PlantState {
	Hidden,
	Rising,
	Holding,
	Falling,
	Die
};

class PiranhaPlant : public Enemy {
private:
	Animation animation;
	const float hiddenhold = 5.0f; // thời gian giữa các lần mọc lên
	const float risetime = 0.5f; // thời gian mọc lên và tụt xuống
	float riseoffset; // chiều cao của cây
	Vector2 basePos; // vị trí mép ống
	const float biteHold = 1.3f;
	float timer = 0;
	const float scale = 5.0f; //3

	PlantState currentState = PlantState::Hidden;
public:
	PiranhaPlant();
	PiranhaPlant(Vector2 pipeTop, MapTheme _theme);
	PiranhaPlant(Vector2 pipeTop, float riseHeight, MapTheme _theme);
	~PiranhaPlant();

	void LoadSource() override;
	void update(float deltatime) override;
	void draw() override;
	bool isDead() override;
	void onDeath(DeathType type, Character* player = nullptr) override;
	void ChangeState(PlantState newState);
	EnemyType getType() const;
	Rectangle getBound() const override;

	void onCollideWith(GameObject* object) override;
};