#pragma once

#include <vector>
#include <raylib.h>

class Animation {
public :
	std::vector <Rectangle> frame;
	float durationtime;
	float currenttime;
	int currentframe;
	bool loop = true;

	Animation();
	void Update(float deltatime);
	bool isFinish() const;
	Rectangle getcurrentframe() const;
	void reset();
};