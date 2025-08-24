#include "../headers/Global.h"
#include "../headers/Map.h"
#include "GameObject.h"
Map* Global::map = nullptr;
Camera2D Global::camera = {};
pair<int,int> Global::level = {1,1};
Character* Global::character = nullptr;


Texture2D resizedImage(const char* imagePath, float width, float height){
    Image img = LoadImage(imagePath);
    if (img.data == NULL) {
        TraceLog(LOG_ERROR, "Failed to load image: %s", imagePath);
        return Texture2D();
    }
    ImageResize(&img, (int)width, (int)height);  
    Texture2D texture = LoadTextureFromImage(img);
    if (texture.id <= 0) {
        TraceLog(LOG_ERROR, "Failed to load texture from image: %s", imagePath);
        UnloadImage(img);  
        return Texture2D(); 
    }
    UnloadImage(img); 
    TraceLog(LOG_INFO, "Successfully loaded file!");
    return texture;  
}

bool operator==(pair<int, int> a, pair<int,int>b){
    return a.first == b.first && a.second == b.second;
}

inline int operator+(int lhs, MapTheme rhs) {
    return lhs + static_cast<int>(rhs);
}

float approach(float current, float target, float increase) {
	if (current < target) {
		return fmin(current + increase, target);
	}
	return fmax(current - increase, target);
}

float lerp(float a, float b, float t) {
    return a + (b - a) * t;
}


Direction getCollisionDirection(GameObject* a, GameObject* b) {
    Rectangle rectA = a->getBound();
    Rectangle rectB = b->getBound();

    float dx = (rectA.x + rectA.width / 2.0f) - (rectB.x + rectB.width / 2.0f);
    float dy = (rectA.y + rectA.height / 2.0f) - (rectB.y + rectB.height / 2.0f);

    float combinedHalfWidth = (rectA.width + rectB.width) / 2.0f;
    float combinedHalfHeight = (rectA.height + rectB.height) / 2.0f;

    float overlapX = combinedHalfWidth - fabsf(dx);
    float overlapY = combinedHalfHeight - fabsf(dy);

    if (overlapX <= 0 || overlapY <= 0)
        return Direction::None;

    if (overlapX < overlapY) {
        return dx > 0 ? Direction::Left : Direction::Right;
    } else {
        return dy > 0 ? Direction::Top : Direction::Bottom;
    }
}


Direction getCollisionDirection(const Rectangle& rectA, const Rectangle& rectB) {
    float dx = (rectA.x + rectA.width / 2.0f) - (rectB.x + rectB.width / 2.0f);
    float dy = (rectA.y + rectA.height / 2.0f) - (rectB.y + rectB.height / 2.0f);

    float combinedHalfWidth = (rectA.width + rectB.width) / 2.0f;
    float combinedHalfHeight = (rectA.height + rectB.height) / 2.0f;

    float overlapX = combinedHalfWidth - fabsf(dx);
    float overlapY = combinedHalfHeight - fabsf(dy);

    if (overlapX <= 0 || overlapY <= 0)
        return Direction::None;

    if (overlapX < overlapY) {
        return dx > 0 ? Direction::Left : Direction::Right;
    } else {
        return dy > 0 ? Direction::Top : Direction::Bottom;
    }
}



ButtonLayoutConfig::ButtonLayoutConfig(int amount_button, int fontSize) {
    this->amount_button = amount_button;
   
    MARGIN_ON = screenHeight * 0.1f;
    MENU_BUTTON_HEIGHT = screenHeight - 2 * MARGIN_ON - 100.0f - 40;

    BUTTON_MARGIN_X = screenWidth * 0.35f;
    FIRST_POSITION_Y_BUTTON = MARGIN_ON + 100.0f;
    BUTTON_SPACING = 15.0f;

    BUTTON_HEIGHT = float(MENU_BUTTON_HEIGHT - BUTTON_SPACING * 2) / amount_button;
    BUTTON_WIDTH = screenWidth / 3;

    FONT_SIZE = fontSize;
}

std::vector<Button*> CreateButtons(const char* buttonLabels[], const ButtonLayoutConfig& other) {
    vector <Button*> buttons(other.amount_button);
    for (int i = 0; i < other.amount_button; i++) {
        buttons[i] = new Button(Singleton<TextureManager>::getInstance().load(TextureType::BUTTON), 
            other.BUTTON_MARGIN_X, 
            other.FIRST_POSITION_Y_BUTTON + i * (other.BUTTON_HEIGHT + other.BUTTON_SPACING),
            other.BUTTON_WIDTH, 
            other.BUTTON_HEIGHT, 
            buttonLabels[i], WHITE, other.FONT_SIZE);
    }
    return buttons;
}