#pragma once
#include <raylib.h>
#include <vector>
#include "Item.h"
using namespace std;

class FireBar : public Item {
private:
    vector<Rectangle> bar;
    Animation fireAnimation;
    float angle;
public:
    FireBar(Vector2 _position, const Animation& ani);

    ~FireBar() = default;
	void update(float dt) override;
    void draw() override;
    void OnCollected(Character* player);
    void checkCollision(Character* player);
    Rectangle getBound() const;
};