#include "../headers/Mario.h"

Mario::Mario() {
	this->position = { 50, 50 };
	speed = 5.0f;
	LoadSource();
}
Mario::Mario(Vector2 position) {
	this->position = position;
	speed = 5.0f;
	LoadSource();
}

void Mario::Update(float deltatime) {
	animation[currentstate].Update(deltatime);
}

void Mario::LoadSource() {
	texture = LoadTexture("../assets/Mario/mario_custom_spritesheet.png");
	
	int texW = 16;
	int texH = 24;
	Animation idle;
	idle.frame = { Rectangle{92, 27, (float) texW, (float) texH}};
	idle.currentframe = 0;
	idle.durationtime = 0.3f;
	idle.currenttime = 0;
	animation[Actionstate::IDLE] = idle;
}

void Mario::Draw() {
	Rectangle currentFrame = animation[currentstate].getcurrentframe();
	float scale = 13.0f;
	Rectangle dest = { position.x, position.y, currentFrame.width * scale, currentFrame.height * scale };
	DrawTexturePro(texture, currentFrame, dest, { 0,0 }, 0, WHITE);

}

void Mario::MoveLeft() { position.x -= speed; }

void Mario::MoveRight() { position.x += speed; }


