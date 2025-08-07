#pragma once
#include <raylib.h>
#include "Enemy.h"
#include "time.h"

class Bowser : public Enemy {
private :
	/*
	Vector2 position;
	Rectangle bound;
	Texture texture;

	Direction direction;
	bool onGround;
	Vector2 velocity;

	MapTheme theme;
	*/

	Animation animations;
	const float scale = 3.0f;
	bool isdied = false;

public :
	Bowser();
	Bowser(Vector2 position, MapTheme theme);
	~Bowser() override;
	void LoadSource() override;
	void draw() override;
	void update(float deltatime) override;
	void onDeath(DeathType type, Character* player = nullptr) override;
	bool isDead() override;

	EnemyType getType() const override;
	Rectangle getBound() const override;

	void onCollideWith(GameObject* object) override; //Collide with enities(character, enemies, item)
};
