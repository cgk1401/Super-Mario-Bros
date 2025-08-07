#include "../headers/Bowser.h"
#include "../headers/TextureManager.h"
#include "../headers/Collision.h"

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
	animations.durationtime = 0.3f;
}

void Bowser::Draw() {
	Rectangle currentframe = animations.getcurrentframe();
	currentframe.width = direction == Direction::Left ? abs(currentframe.width) : -abs(currentframe.width);
	
	bound = { position.x, position.y, currentframe.width * scale, currentframe.height * scale };
	DrawTexturePro(texture, currentframe, bound, { 0,0 }, 0, WHITE);
	
	DrawFireBreath();
}

void Bowser::Update(float deltatime, Map* map) {
	animations.Update(deltatime);

	UpdateFireBreath(deltatime);
	cout << fireballs.size() << endl;

	jumpTimer += deltatime;

	if (onGround && jumpTimer >= jumpCooldown) {
		Jump();
		jumpTimer = 0.0f;
	}

	if (!onGround) {
		velocity.y += 800.0f * deltatime;
	}
	else {
		velocity.y = 0;
	}

	if (movingRight) {
		velocity.x = moveSpeed;
	}
	else {
		velocity.x = -moveSpeed;
	}

	moved += fabs(velocity.x * deltatime);

	if (moved >= moveDistance) {
		movingRight = !movingRight;
		moved = 0.0f;
		if (onGround) {
			Jump();
			jumpTimer = 0.0f;
		}
	}
	

	position.x += velocity.x * deltatime;
	position.y += velocity.y * deltatime;

	Rectangle currentFrame = animations.getcurrentframe();
	bound = { position.x, position.y, currentFrame.width * scale, currentFrame.height * scale };

	CreateFireBalls(deltatime);

	Collision::handleEnemyCollision(this, map);

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

void Bowser::Jump() {
	velocity.y = jumpForce;
	onGround = false;
}

void Bowser::DrawFireBreath() {
	for (auto& it : fireballs) {
		it->Draw();
	}
}

void Bowser::CreateFireBalls(float deltatime) {
	fireBreathTimer += deltatime;
	
	if (fireBreathTimer >= fireBreathCooldown) {
		fireBreathTimer = 0.0f;
		if (Global::character != nullptr) {
			fireballs.push_back(new BowserFireBall({ position.x, position.y }, Global::character->getPosition().y));
		}
	}
}

void Bowser::UpdateFireBreath(float deltatime) {
	for (auto& it : fireballs) {
		it->Update(deltatime);
	}
	RemoveFireBreath();
}

void Bowser::RemoveFireBreath() {
	for (auto it = fireballs.begin(); it != fireballs.end();) {
		if ((*it)->getIsActive() == false) {
			it = fireballs.erase(it);
		}
		else {
			it++;
		}
	}
}

