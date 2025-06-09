#include "../headers/Mario.h"

Mario::Mario(Vector2 position) {
	this->position = position;
	speed = 5.0f;
	LoadSource();
}

void Mario::Update(float deltatime) {
	animation[currentstate].Update(deltatime);
}

void Mario::LoadSource() {
	texture = LoadTexture(".....");

	Animation idle;
	idle.frame = { {}, {}, {} };
	idle.currentframe = 0;
	idle.durationtime = 0.3f;
	idle.currenttime = 0;
	animation[Actionstate::IDLE] = idle;
}

void Mario::Draw() {
	Rectangle currentFrame = animation[currentstate].getcurrentframe();
	float scale = 3.0f;
	Rectangle dest = { position.x, position.y, currentFrame.x * scale, currentFrame.y * scale };
	DrawTexturePro(texture, currentFrame, dest, { 0,0 }, 0, WHITE);

}

void Mario::MoveLeft() { position.x -= speed; }

void Mario::MoveRight() { position.x += speed; }


