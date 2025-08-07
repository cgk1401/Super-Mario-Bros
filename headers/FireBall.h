#pragma once

#include <raylib.h>
#include "Animation.h"
#include "CharacterState.h"
#include "Character.h"
#include "Item.h"
class FireState;

class FireBall : public Item{
	friend class FireState;
	friend class Collision;
private:
	Vector2 position;
	Vector2 velocity;

	Animation* animation;
	float scale;
	bool onGround = false;

	const float FIREBALL_SPEEDX = 850.0f; //350
	const float FIREBALL_SPEEDY = 3800.0f; //800
	const float FIREBALL_LIFETIME = 2.0f;
	const float BOUNCE_VELOCITY = -500.f; //-200

	//bool isActive;
	float positionGround;
	float currentLifeTime;
public:
	FireBall(Character* character, float positionGround);
	FireBall(Vector2 position, Character* character, float positionGround);
	~FireBall();

	bool isActive;
	void SetAnimation(Character* character);
	void SetVelocity(Vector2 velocity);
	void update(float deltatime) override;
	void draw() override;
	void Deactivate();
	void explode();

	void ActiveStatus(float deltatime);

	Rectangle getBound() const override;

	void onFootCollision(Tile& tile, int row, int col, Map* map, MapTileInstance* tileInstance) override;
    void onGeneralCollision(Direction collideSide, Tile& tile, int row, int col, Map* map, MapTileInstance* tileInstance) override;
    void onHeadCollision(Tile& tile, int row, int col, Map* map, MapTileInstance* tileInstance) override;
	void OnCollected(Character* player) override{};
	void onCollideWith(GameObject* object) override;
};