#include "../headers/Animation.h"

Animation::Animation() : durationtime(0.0f), currentframe(0), currenttime(0.0f){}

void Animation::Update(float deltatime) {
	currenttime += deltatime;
	if (currenttime >= durationtime) {
		currenttime = 0;
		currentframe = (currentframe + 1) % frame.size();
	}
}

Rectangle Animation::getcurrentframe() {
	return frame[currentframe];
}

void Animation::reset(){
	 currenttime = 0;
    currentframe = 0;
}
