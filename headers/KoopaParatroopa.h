#pragma once

#include "Enemy.h"

enum class KoopParatroopState {
	Alive,
	Die,
};

class KoopaParatroop : public Enemy {
private :
	Animation animations;
	bool movingDown = true;
	const float gravity = 150;
	const float speedY = 100;
	const float distance = 150;
	const float scale = 3.0f;

	float destinationAbove;
	float destinationBelow;

	KoopParatroopState currentState = KoopParatroopState::Alive;

public :
	KoopaParatroop();
	KoopaParatroop(Vector2 position, MapTheme theme);

	~KoopaParatroop() override;
	void LoadSource() override;
	void setDistance();
	void onDeath(DeathType type, Character* player = nullptr) override;
	bool isDead() override;
	void ChangeState(KoopParatroopState state);

	EnemyType getType() const override;

	void draw() override;
	void update(float deltatime) override;
	Rectangle getBound() const override;

	void CreateFrame(Animation& animations, KoopParatroopState currentState = KoopParatroopState::Alive);

	void onCollideWith(GameObject* object) override;
};