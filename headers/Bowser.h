#pragma once

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
	
	vector <BowserFireBall*> fireballs;
	float fireBreathCooldown = 2.0f;
	float fireBreathTimer = 0.0f;

public :
	Bowser();
	Bowser(Vector2 position, MapTheme theme);
	~Bowser() override;
	void LoadSource() override;
	void Draw() override;
	void Update(float deltatime, Map* map) override;
	void onDeath(DeathType type, Character* player = nullptr) override;
	bool isDead() override;

	EnemyType getType() const override;
	void Jump();

	// BowserFireball
	void DrawFireBreath();
	void CreateFireBalls(float deltatime);
	void UpdateFireBreath(float deltatime);
	void CheckCollisionWithCharacter();
	void RemoveFireBreath();
	vector <BowserFireBall*> getBowserFireball();
	
};
