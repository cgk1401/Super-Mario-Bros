#include "../headers/Bowser.h"
#include "../headers/TextureManager.h"

Bowser::Bowser():Enemy(){
	this->position = { 150, 900 };
	LoadSource();
}

Bowser::Bowser(Vector2 position, MapTheme theme) : Enemy() {
	this->position = position;
	this->theme = theme;
	LoadSource();
}

Bowser::~Bowser() {}

void Bowser::LoadSource() {
	cout << "Bowser-------------\n";
	cout << "Position Bowser " << position.x << ":" << position.y << endl;
	texture = Singleton<TextureManager>::getInstance().load(TextureType::ENEMY);

	animations.frame.push_back({ 0 + (float)theme * 146, 208, 32, 32 });
	animations.frame.push_back({ 34 + (float)theme * 146, 208, 32, 32});
	animations.frame.push_back({ 68 + (float)theme * 146, 208, 32, 32 });
	animations.frame.push_back({ 102 + (float)theme * 146, 208, 32, 32 });
	animations.currentframe = 0;
	animations.currenttime = 0.0f;
	animations.durationtime = 0.1f;
}

void Bowser::draw() {
	Rectangle currentframe = animations.getcurrentframe();
	currentframe.width = direction == Direction::Left ? abs(currentframe.width) : -abs(currentframe.width);
	
	Rectangle dest = { position.x, position.y, currentframe.width * scale, currentframe.height * scale };
	DrawTexturePro(texture, currentframe, dest, { 0,0 }, 0, WHITE);
}

void Bowser::update(float deltatime) {
	animations.Update(deltatime);
}

void Bowser::onDeath(DeathType type, Character* player)
{
}

bool Bowser::isDead() {
	return position.y >= screenHeight + 50;
}

EnemyType Bowser::getType() const {
	return EnemyType::BOWSER;
}


Rectangle Bowser::getBound() const {
	Rectangle frame = animations.getcurrentframe();
	float delta = 2.0f; //narrow the width
	return {
		position.x + delta,
		position.y,
		frame.width * scale - delta * 2,
		frame.height * scale
	};
}

void Bowser::onCollideWith(GameObject* object) {
	
}
