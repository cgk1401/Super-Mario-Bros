#include "../headers/ConcreteTileBehavior.h"

void BrickTileBehavior::onHeadCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) {}
void BrickTileBehavior::onFootCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) {}
void BrickTileBehavior::onGeneralCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) {}
bool BrickTileBehavior::isSolid() {
	return true;
}
void QuestionTileBehavior::onHeadCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) {}
void QuestionTileBehavior::onFootCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) {}
void QuestionTileBehavior::onGeneralCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) {}
bool QuestionTileBehavior::isSolid() {
	return true;
}
void CoinTileBehavior::onHeadCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) {}
void CoinTileBehavior::onHeadCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) {}
void CoinTileBehavior::onFootCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) {}
void CoinTileBehavior::onGeneralCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) {}
bool CoinTileBehavior::isSolid() {
	return true; 
}
