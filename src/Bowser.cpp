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

	// OVERWORLD, UNDERGROUND && CASTLE, UNDERWATER
	if (theme == MapTheme::OVERWORLD) {
		animations.frame.push_back({ 0, 208, 32, 32 });
		animations.frame.push_back({ 34, 208, 32, 32 });
		animations.frame.push_back({ 68, 208, 32, 32 });
		animations.frame.push_back({ 102, 208, 32, 32 });
	}
	else if (theme == MapTheme::UNDERGROUND || theme == MapTheme::CASTLE) {
		animations.frame.push_back({ 0 + 146, 208, 32, 32 });
		animations.frame.push_back({ 34 + 146, 208, 32, 32 });
		animations.frame.push_back({ 68 + 146, 208, 32, 32 });
		animations.frame.push_back({ 102 + 146, 208, 32, 32 });
	}
	else if (theme == MapTheme::UNDERWATER) {
		animations.frame.push_back({ 0 + 2 * 146, 208, 32, 32 });
		animations.frame.push_back({ 34 + 2 * 146, 208, 32, 32 });
		animations.frame.push_back({ 68 + 2 * 146, 208, 32, 32 });
		animations.frame.push_back({ 102 + 2 * 146, 208, 32, 32 });
	}
	animations.currentframe = 0;
	animations.currenttime = 0.0f;
	animations.durationtime = 0.1f;
}

void Bowser::Draw() {
	Rectangle currentframe = animations.getcurrentframe();
	currentframe.width = direction == Direction::Left ? abs(currentframe.width) : -abs(currentframe.width);
	
	bound = { position.x, position.y, currentframe.width * scale, currentframe.height * scale };
	DrawTexturePro(texture, currentframe, bound, { 0,0 }, 0, WHITE);
}

void Bowser::Update(float deltatime, Map* map) {
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
