#pragma once
#include <raylib.h>
#include <vector>
#include "Item.h"
using namespace std;

class FireBar : public Item {
private:
    Texture2D texture;
    vector<Rectangle> bar;
    Animation fireAnimation;
    float angle;
public:
    FireBar(Vector2 _position, const Animation& ani);

    ~FireBar() = default;
	void Update(float dt);
    void Draw(const Texture& texure);
    void OnCollected(Character* player);
    void checkCollision(Character* player);
    Rectangle getBound() const;
};