#include "../headers/InputHandler.h"

InputHandler::InputHandler() {
	bindKey(KEY_LEFT, new MoveLeft());
	bindKey(KEY_RIGHT, new MoveRight());
}

void InputHandler::bindKey(int key, Command* command) {
	input[key] = command;
}

void InputHandler::HandInput(Character* character) {
	for (auto& [key, command] : input) {
		if (IsKeyDown(key)) {
			command->Excute(character);
		}
	}
}