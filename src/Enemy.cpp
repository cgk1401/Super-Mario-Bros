#include "Enemy.h"

Enemy::Enemy() :
	texture({ 0 }),
	direction(Direction::Left),
	theme(MapTheme::OVERWORLD) {}

void Enemy::changeDirection(Direction newDirection) {
	if (direction != newDirection)
		direction = newDirection;
}

bool Enemy::isActive() const {
	Vector2 screenPos = GetWorldToScreen2D(this->position, Global::camera);
	float tolerance = Map::TILE_SIZE;
	return (
		screenPos.x <= screenWidth + tolerance &&
		screenPos.y >= -tolerance &&
		screenPos.y <= screenHeight + tolerance
		);
}

ObjectType Enemy::getObjectType() const {
	return ObjectType::ENEMY;
}

void Enemy::onFootCollision(Tile& tile, int row, int col, Map* map, MapTileInstance* tileInstance)  {
	if (tileInstance->offsetPos.y != 0) {
		onDeath(DeathType::FALLING);
	}
	else if (auto brickstate = dynamic_cast<BrickTileState*>(tileInstance->state)) {
		if (brickstate->hasBroken == true)
			onDeath(DeathType::FALLING);
	}
}
void Enemy::onGeneralCollision(Direction collideSide, Tile& tile, int row, int col, Map* map, MapTileInstance* tileInstance)  {
	if (collideSide == Direction::Left) {
		direction = Direction::Right;
	}
	else direction = Direction::Left;
}
void Enemy::onHeadCollision(Tile& tile, int row, int col, Map* map, MapTileInstance* tileInstance)  {}
