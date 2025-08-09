#pragma once

#include "Lift.h"
using namespace std;

class Horizontal : public Lift {
private :
	const float speedX = 100.0f;
	const float scale = 3.0f;

	const float distance = 100.0f;
	float destinationLeft;
	float destinationRight;
	bool movingLeft = true;

	void SetDestination();
public :
	Horizontal();
	Horizontal(Vector2 position);
	~Horizontal() override {};

	void LoadSource() override;
	void Update(float deltatime) override;
    void Draw() override;
    Rectangle getBound() override;
};