#pragma once

#include <vector>
#include <raylib.h>

class Animation {
public :
	std::vector <Rectangle> frame;
	float durationtime;
	float currenttime;
	int currentframe;

	Animation();
	void Update(float deltatime);

	Rectangle getcurrentframe();
	void reset();
	
};