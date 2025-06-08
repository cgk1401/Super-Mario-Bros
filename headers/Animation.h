#pragma once

#include <vector>
#include <raylib.h>

class Animation {
public :
	std::vector <Rectangle> frame;
	float durationtime;
	float currenttime;
	int currentframe;

public :
	Animation();
	void Update(float deltatime);

	Rectangle getcurrentframe();
};