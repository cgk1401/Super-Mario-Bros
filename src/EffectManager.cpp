#include "../headers/EffectManager.h"
#include "../headers/CoinCollectEffect.h"
#include <algorithm>
#include "../headers/Map.h"
#include "../headers/TextureManager.h"
#include "../headers/FireBallExplosionEffect.h"
#include "../headers/GoombaDeadEffect.h"
#include "../headers/MarioDeadEffect.h"
#include "../headers/KoopaDeathEffect.h"

EffectManager::EffectManager(){
    texture = Singleton<TextureManager>::getInstance().load(TextureType::ITEM);

    //BRICK BREAK
   
   
}

void EffectManager::spawnBrickBreak(int row, int col, MapTheme theme){
    float x =(float) col * Map::TILE_SIZE;
    float y =(float) row * Map::TILE_SIZE;

    Vector2 spawnPos = { x + Map::TILE_SIZE / 2 - 8, y + Map::TILE_SIZE / 2 - 8 }; // căn giữa tile
    
    effects.emplace_back(new BrickBreakEffect(spawnPos, theme));
    
}

void EffectManager::spawnCoin(int row, int col){
     float x =(float) col * Map::TILE_SIZE;
    float y =(float) row * Map::TILE_SIZE;

    Vector2 spawnPos = { x + Map::TILE_SIZE / 2 - 8, y};
    hidden_effects.emplace_back(new CoinCollectEffect(spawnPos));
}

void EffectManager::explosionEffect(Vector2 pos){
    
    effects.emplace_back(new FireBallExplosionEffect(pos));
}

void EffectManager::goombaDead(Vector2 pos){
    effects.emplace_back(new GoombaDeadEffect(pos));
}
void EffectManager::marioDead(Vector2 position, const Texture2D& texture, Rectangle frame){
    effects.emplace_back(new MarioDeadEffect(position, texture, frame));
}
void EffectManager::koopaDeath(Vector2 position, const Texture2D& texture, Rectangle frame){
    effects.emplace_back(new KoopaDeathEffect(position, texture, frame));
}

void EffectManager::koopaDeath(Vector2 position, const Texture2D& texture, Animation animations) {
    cout << "Effet animation\n";
    effects.emplace_back(new KoopaDeathEffect(position, texture, animations));
}

void EffectManager::onNotify(const EventType& event, void* data){
    map<EventType, EventInfo> eventMap = Singleton<EventDataBase>::getInstance().getMap();
    auto it = eventMap.find(event);
    if(it == eventMap.end()) return;

    Vector2* position = static_cast<Vector2*>(data);
    if (position) effects.emplace_back(new PointEffect(*position, event));
}
void EffectManager::update(float dt){
    for(auto& e : effects){
        e->update(dt);
    }
    for(auto& h_e : hidden_effects){
        h_e->update(dt);
    }
    //xoa nhung effect da hoan thanh
    effects.erase(
        remove_if(effects.begin(), effects.end(),
            [](BaseEffect* e) {
                return e->isFinished();
            }),
        effects.end()
    );

     hidden_effects.erase(
        remove_if(hidden_effects.begin(), hidden_effects.end(),
            [](BaseEffect* e) {
                return e->isFinished();
            }),
        hidden_effects.end()
    );

}

void EffectManager::draw(){
    for(auto& b : effects){
        b->draw(texture);
    }
}


void EffectManager::drawHiddenEffects(){
    for(auto& b: hidden_effects){
        b->draw(texture);
    }
}