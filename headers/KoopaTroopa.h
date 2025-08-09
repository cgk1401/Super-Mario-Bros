#pragma once

#include "Animation.h"
#include "Enemy.h"
#include <map>
using namespace std;

enum class KoopaState {
	Walk,
	Shell,
	Die, //falling off (die by fireball)
	RedWalk,
	RedShell,
	RedDie,
};

class KoopTroopa : public Enemy{
	friend class Collision;
private :
	map <KoopaState, Animation> animation;
	KoopaState currentState;

	const float walkSpeed = 100.0f;
	const float shellSpeed = 500.0f;

	bool isStationary = false;
	float gravity = 1000; // vận tốc rơi
	const float scale = 3.0f;
	EnemyType enemyType;

public :
	KoopTroopa(EnemyType type);
	KoopTroopa(Vector2 position, EnemyType type, MapTheme _theme);
	~KoopTroopa() override;

	void LoadSource() override;
	
	void onDeath(DeathType type, Character* player = nullptr) override;
	bool isDead() override;

	void moveLeft();
	void moveRight();
	void Fall();
	void draw() override;
	void update(float deltatime) override;

	EnemyType getType() const;
	Rectangle getBound() const override;
	void onFootCollision(Tile& tile, int row, int col, Map* map, MapTileInstance* tileInstance) override;
    void onCollideWith(GameObject* object) override;

};