#pragma once

#include "Animation.h"
#include "Item.h"
#include <raylib.h>

using namespace std;

class Lift : public Item{
protected:
	Texture2D texture;
	Animation animations;
    Vector2 velocity;
    Vector2 position;
	Rectangle bound;

public :
    Lift() : texture{ 0 }, 
        animations{}, 
        velocity{ 0.0f, 0.0f }, 
        position{ 0.0f, 0.0f },
        bound{ 0.0f, 0.0f, 0.0f, 0.0f } 
    {
        interactWithMap = false;
    };

    Lift(Vector2 position) : texture{ 0 },
        animations{},
        velocity{ 0.0f, 0.0f },
        position (position),
        bound{ 0.0f, 0.0f, 0.0f, 0.0f } 
    {
        interactWithMap = false;
    };

	virtual ~Lift() { UnloadTexture(texture); }

	virtual void LoadSource() = 0;
	virtual void update(float deltatime) override = 0;
	virtual void draw() override = 0;
	virtual Rectangle getBound() const override = 0;
	virtual Vector2 getVelocity() {
		return this->velocity;
	}
	virtual void onCollideWith(GameObject* object) override = 0;

    void OnCollected(Character* player) override {}
};