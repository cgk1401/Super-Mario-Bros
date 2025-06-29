#pragma once

#include "Animation.h"
#include "Enemy.h"
#include <map>
using namespace std;

enum class KoopaState {
	Walk,
	Shell
};

enum class DirectionKoopa {
	Left,
	Right
};
class KoopTroopa : public Enemy {
private :
	map <KoopaState, Animation> animation;
	KoopaState currentState = KoopaState::Walk;
	DirectionKoopa currentDirection = DirectionKoopa::Left;

	const float walkSpeed = 3.0f;
	const float shellSpeed = 8.0f;

	float gravity = 0.5f; // vận tốc rơi
	float velocity = 0;
	const float scale = 3.0f;
	bool onGround = true;

public :
	KoopTroopa();
	KoopTroopa(Vector2 position);
	~KoopTroopa() override;

	void LoadSource() override;
	void Draw() override;
	void Update(float deltatime) override;
	void moveLeft();
	void moveRight();
	void ChangeDirection(DirectionKoopa direction);
	void Fall();
};