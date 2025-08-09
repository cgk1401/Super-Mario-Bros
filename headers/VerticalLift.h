#pragma once
#include "Lift.h"

using namespace std;

class VerticalLift : public Lift {
private :
	const float speedY = 60.0f;
	const float scale = 3.0f;

	const float distance = 120.0f;
	float destinationBelow;
	float destinationAbove;
	bool movingDown = true;

public :
	VerticalLift();
	VerticalLift(Vector2 position);

	~VerticalLift() override {};

	void LoadSource() override;
	void Update(float deltatime) override;
    void Draw() override;
    Rectangle getBound() override;
};