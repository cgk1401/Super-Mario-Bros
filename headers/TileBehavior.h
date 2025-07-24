#pragma once

class Map;
struct MapTileInstance;
class Character;

//Các hành vi của từng tile trong map
struct TileState {
    virtual ~TileState() = default;
};

//Strategy Pattern
class TileBehavior {
public:
 	virtual TileBehavior* clone() const = 0;
	virtual void onHeadCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) = 0; //sau khi chạm đầu thì thay đổi behavior(chạm vào brick thì bị vỡ -> biên mất)
	virtual void onFootCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) = 0; 
	virtual void onGeneralCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) = 0;
	virtual void update(float dt, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) = 0;
	virtual bool isSolid() = 0;
	virtual ~TileBehavior() = default;
};
