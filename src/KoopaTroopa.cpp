#include "../Headers/KoopaTroopa.h"

KoopTroopa::KoopTroopa() : Enemy() {
	this->position = { 200, 200 };
	LoadSource();
}

KoopTroopa::KoopTroopa(Vector2 position) {
	this->position = position;
	LoadSource();
}

KoopTroopa::~KoopTroopa() {
	if (texture.id != 0) {
		UnloadTexture(texture);
	}
}

void KoopTroopa::LoadSource() {
	texture = LoadTexture("../assets/Enemy/Enemies_Bosses.png");

	Animation walk;
	walk.currentframe = 0;
	walk.currenttime = 0;
	walk.durationtime = 0.3f;
	walk.frame.push_back({ 0, 112, 16, 24 });
	walk.frame.push_back({ 18, 112, 16, 24 });
	animation[KoopaState::Walk] = walk;

	Animation shell;
	shell.currentframe = 0;
	shell.currenttime = 0;
	shell.durationtime = 0.2;
	shell.frame.push_back({ 72, 120, 16, 16 });
	animation[KoopaState::Shell] = shell;

}

void KoopTroopa::Draw() {
	Rectangle currentframe = animation[currentState].getcurrentframe();
	currentframe.width = currentDirection == DirectionKoopa::Left ? abs(currentframe.width) : -abs(currentframe.width);

	bound = { position.x, position.y, currentframe.width * scale, currentframe.height * scale };
	DrawTexturePro(texture, currentframe, bound, { 0,0 }, 0, WHITE);
}

void KoopTroopa::Update(float deltatime) {
	animation[currentState].Update(deltatime);
}

void KoopTroopa::moveLeft() {
	if (currentState == KoopaState::Walk) {
		position.x -= walkSpeed;
	}
	else if (currentState == KoopaState::Shell) {
		position.x -= shellSpeed;
	}
}

void KoopTroopa::moveRight() {
	if (currentState == KoopaState::Walk) {
		position.x += walkSpeed;
	}
	else if (currentState == KoopaState::Shell) {
		position.x += shellSpeed;
	}
}

void KoopTroopa::ChangeDirection(DirectionKoopa direction) {
	currentDirection = direction;
}

void KoopTroopa::Fall() {
	velocity += gravity;
	position.y += velocity;
}