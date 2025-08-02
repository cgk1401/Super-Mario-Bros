#pragma once

#include "Enemy.h"
#include <map>
#include "Animation.h"

using namespace std;

enum class RedKoopaState {
	Walk,
	Shell,
	Die, //falling off (die by fireball)
};

class RedKoopaTroopa : public Enemy {
	friend class Collsion;
private :
	map <RedKoopaState, Animation> animations;

	RedKoopaState currentState;

	const float walkSpeed = 100.0f;
	const float shellSpeed = 500.0f;

	bool isStationary = false;
	float gravity = 1000; // vận tốc rơi
	const float scale = 3.0f;

public :
	RedKoopaTroopa();
	RedKoopaTroopa(Vector2 position, MapTheme _theme);
	~RedKoopaTroopa() override;

	void LoadSource() override;
	void Draw() override;
	void Update(float deltatime, Map* map) override;
	void onDeath(DeathType type, Character* player = nullptr) override;
	bool isDead() override;

	void moveLeft();
	void moveRight();
	void Fall();

	EnemyType getType() const;
};