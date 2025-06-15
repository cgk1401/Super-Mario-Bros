#pragma once
#include "TileBehavior.h"
//Strategy pattern

//ko là block gì hết
class EmptyTileBehavior : public TileBehavior {
public:
	void onHeadCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) override{}
	void onFootCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) override{}
	void onGenerallCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) override{}
	bool isSolid() override { return false; }
	~EmptyTileBehavior() = default;
};


class SolidTileBehavior : public TileBehavior { //dùng chugn cho ground + mấy block đứng lên dc nhưng ko chứa item hay hiệu ứng j (pipe, ...)
public:
	void onHeadCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) override{}
	void onFootCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) override{}
	void onGenerallCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) override{}
	bool isSolid() override { return true; }
	~SolidTileBehavior() = default;
};

class BrickTileBehavior : public TileBehavior {
public:
	void onHeadCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) override{} // bị vỡ ra -> add effect mảnh vỡ
	void onFootCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) override{} // đứng lên thì ko sao -> giống solid -> dùng lại SolidTileBehavior::onFootCollision(..)
	void onGenerallCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) override{} // tương tự
	bool isSolid() override{} 
	~BrickTileBehavior() = default;
};

class QuestionTileBehavior : public TileBehavior { // sẽ xuất hiện coin(chủ yếu), xuất hiện mushroom khi đang ở dạng nhỏ xí, xuất hiện flower khi đang ở dạng super cấp 1, star thì ....
public:
	void onHeadCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) override{}
	void onFootCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) override{}
	void onGenerallCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) override{}
	bool isSolid() override{}
	~QuestionTileBehavior() = default;
};

class CoinTileBehavior : public TileBehavior {
public:
	void onHeadCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) override{}
	void onFootCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) override{}
	void onGenerallCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) override{}
	bool isSolid() override{}
	~CoinTileBehavior() = default;
};

//Thêm các loại tile behavior dô, đảm bảo rằng ko bị trùng nha (ví dụ PipeTile thì đã sử dụng behavior từ SolidTileBehavior r nên không cần tạo class mới nữa...





