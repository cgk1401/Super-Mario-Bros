#include "../headers/TextureManager.h"
#include <string>

TextureManager* TextureManager::instance = nullptr;

TextureManager::TextureManager(){
    texture.emplace(TextureType::MARIO, LoadTexture("../assets/Mario/Mario & Luigi.png"));
    texture.emplace(TextureType::MARIOINVINCIBILITY, LoadTexture("../assets/Mario/mario_luigi_4.png"));
    texture.emplace(TextureType::ENEMY, LoadTexture("../assets/Enemy/Enemies_Bosses.png"));
    texture.emplace(TextureType::BUTTON, LoadTexture("../assets/GUI/Button.png"));
    texture.emplace(TextureType::ITEM, LoadTexture("../assets/Item/Items Objects and NPCs.png"));
}

 TextureManager::~TextureManager(){
    for(auto& it: texture){
        UnloadTexture(it.second);
    }
    texture.clear();
 }


Texture2D& TextureManager::load(TextureType type){
    // if (texture.find(type) == texture.end()) {
    //    TraceLog(LOG_ERROR, "INVALID TYPE");
    //    return ;
    //}
    return texture[type];
}

