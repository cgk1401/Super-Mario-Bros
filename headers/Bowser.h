#pragma once
#include <raylib.h>
#include "Enemy.h"
#include "time.h"
#include "BowserFireBall.h"
#include <vector>
#include "CharacterState.h"
#include "PlayState.h"
using namespace std;

class Bowser : public Enemy{
private :
	Animation animations;
	const float scale = 3.0f;
	bool isdied = false;

	float moveDistance = 120.0f;
	float moved = 0.0f;
	float moveSpeed = 50.0f;
	float jumpForce = -500.0f; 
	float jumpCooldown = 3.0f;
	float jumpTimer = 0.0f;
	bool movingRight = true;
	
	float fireBreathCooldown = 2.0f;
	float fireBreathTimer = 0.0f;

public :
	Bowser();
	Bowser(Vector2 position, MapTheme theme);
	~Bowser() override;
	void LoadSource() override;
	void draw() override;
	void update(float deltatime) override;
	void onDeath(DeathType type, Character* player = nullptr) override;
	bool isDead() override;
	bool FollowPlayer() const override{return true;}

	EnemyType getType() const override;
	Rectangle getBound() const override;

	void onCollideWith(GameObject* object) override; //Collide with enities(character, enemies, item)
	void Jump();

	// BowserFireball
	void CreateFireBalls(float deltatime);
};
