#include "../headers/ConcreteTileBehavior.h"
#include "../headers/Character.h"
#include "../headers/Map.h"
#include "../headers/Item.h"
#include "../headers/Flower.h"
#include "../headers/Mushrooom.h"
#include "../headers/Star.h"

void BrickTileBehavior::onHeadCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) {
	map->setTile(tileRow, tileCol, 0);
}
void BrickTileBehavior::onFootCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) {}
void BrickTileBehavior::onGeneralCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) {}
bool BrickTileBehavior::isSolid() {
	return true;
}
void QuestionTileBehavior::onHeadCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) {
	Item* item = nullptr;
	item = new Flower(Vector2(tileRow, tileCol));
	if (1) {
		item = new Mushroom(Vector2(tileRow, tileCol));
	}
	else if (2) {
		item = new Flower(Vector2(tileRow, tileCol));
	}
	else if (3) {
		item = new Star(Vector2(tileRow, tileCol));
	}
}
void QuestionTileBehavior::onFootCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) {}
void QuestionTileBehavior::onGeneralCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) {}
bool QuestionTileBehavior::isSolid() {
	return true;
}
void CoinTileBehavior::onHeadCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) {

}
void CoinTileBehavior::onHeadCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) {}
void CoinTileBehavior::onFootCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) {}
void CoinTileBehavior::onGeneralCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) {}
bool CoinTileBehavior::isSolid() {
	return true; 
}
