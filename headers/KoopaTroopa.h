#pragma once

#include "Animation.h"
#include "Enemy.h"
#include <map>
using namespace std;

enum class KoopaState {
	Walk,
	Shell,
	Die, //falling off (die by fireball)
};

class KoopTroopa : public Enemy {
	friend class Collision;
private :
	map <KoopaState, Animation> animation;
	KoopaState currentState;

	const float walkSpeed = 100.0f;
	const float shellSpeed = 500.0f;

	bool isStationary = false;
	float gravity = 1000; // vận tốc rơi
	const float scale = 3.0f;

public :
	KoopTroopa();
	KoopTroopa(Vector2 position);
	~KoopTroopa() override;

	void LoadSource() override;
	void Draw() override;
	void Update(float deltatime, Map* map) override;
	void onDeath(DeathType type, Character* player = nullptr) override;
	bool isDead() override;

	void moveLeft();
	void moveRight();
	void Fall();
	
};