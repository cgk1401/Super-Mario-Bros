#pragma once
#include <map>
#include "../headers/Command.h"
#include "raylib.h"

class InputHandler {
private :
	std::map <int, Command*> input;

public :
	InputHandler();
	
	void bindKey(int key, Command* command);
	void HandInput(Character* character);
};