#include "../headers/Mario.h"

Mario::Mario(Vector2 position) {
	this->position = position;
	LoadSource();
}

void Mario::Update(float deltatime) {
	animation[currentstate].Update(deltatime);
}

void Mario::LoadSource() {
	texture = LoadTexture(".....");

	Animation idle;

	idle.frame = { {11, 18, 12, 16}, {43,17, 15, 16}, {76, 17, 15, 16} };// test thử
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
