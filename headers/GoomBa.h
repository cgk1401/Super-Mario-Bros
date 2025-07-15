#pragma once
#include "Enemy.h"
#include "Timer.h"
#include <map>
using namespace std;

enum class GoomBaState {
	Run,
	DIE_STOMP,
	DIE_FALLING
};

class GoomBa : public Enemy {
private:
	map <GoomBaState, Animation> animation;
	GoomBaState currentState = GoomBaState::Run;
	const float speed = 100.0f;
	const float scale = 3.0f;
	float jump = -10;
	float gravity = 50;
	Timer stomp_dead_timer;
public:
	GoomBa();
	GoomBa(Vector2 position);
	~GoomBa() override;

	void LoadSource() override;
	void Draw() override;
	void Update(float deltatime, Map* map) override;
	void DIE(Character* player) override;
	bool isDead() override;

	void moveLeft(); // goomba luôn di chuyển sang trái tấn công character
	void moveRight(); // gặp chướng ngại vật(map, ống) goomba di chuyển sang phải
	void moveUp(); // xảy ra khi goomba bị rùa tấn công, goomba sẽ nhảy lên sau đó die

	void ChangeState(GoomBaState newState); // thay đổi trạng thái khi collision
};