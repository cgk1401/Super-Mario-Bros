#include "../headers/ItemManager.h"
#include "../headers/TextureManager.h"
#include "../headers/Collision.h"
#include "../headers/Coin.h"
#include "FireBar.h"
ItemManager::ItemManager(){
    texture = Singleton<TextureManager>::getInstance().load(TextureType::ITEM);

    mushroomAni.durationtime = 0.1;
    mushroomAni.frame.push_back({0, 8 , 16, 16});

    flowerAni.durationtime = 0.3f;
    for(int i = 0 ;i < 4; ++i){
        flowerAni.frame.push_back({(float)(32 + 18 * i), 8, 16, 16});
    }

    starAni.durationtime = 0.3f;
    for(int i = 0 ;i < 4; ++i){
        starAni.frame.push_back({(float)(106 + 18 * i), 8, 16, 16});
    }
    for (int i = 0; i < 4; i++) {
        coinAni.frame.push_back({180 + (float) i * 10 , 36, 8, 16});
    }
    coinAni.durationtime = 0.1f;


}

ItemManager::~ItemManager() {
    for (auto i : items) delete i;
    items.clear();  
}

void ItemManager::Spawn(ItemType type, Vector2 position, void* extra_data) {
    Item* item = nullptr;
    switch (type) {
        case ItemType::MUSHROOM:
            item = new Mushroom(position, mushroomAni); break;
        case ItemType::FLOWER:
            item = new Flower(position, flowerAni); break;
        case ItemType::STAR:
            item = new Star(position, starAni); break;
        case ItemType::COIN:
            item = new Coin(position, coinAni); break;
        case ItemType::FIRE_BAR:
            item = new FireBar(position, firebarAni); break;
        case ItemType::BOWSER_FIRE_BALL:{
            float* positionDestinationY = static_cast<float*>(extra_data);
            if(positionDestinationY) 
                item = new BowserFireBall(position, *positionDestinationY);
            break;
        }
    }
    if (item) {
        if(auto f = dynamic_cast<FireBar*>(item)){
            items.push_back(item);
        }
        else
            hiddenItems.push_back(item);
    }
}

void ItemManager::Update(float dt, Character* player, Map* map) {
    for (auto item : items) {
        item->update(dt);
        FireBar* f = dynamic_cast<FireBar*>(item);
        if(f)
        {
            f->checkCollision(player);
        }
    }

    for(auto& item: hiddenItems){
        item->update(dt);
    }
    // Erase collected items
    items.erase(remove_if(items.begin(), items.end(),
        [](Item* i) {
            if (i->collected || i->position.y > GetScreenHeight() + 50) { delete i; return true; }
            return false;
        }), items.end());
    hiddenItems.erase(remove_if(hiddenItems.begin(), hiddenItems.end(),
        [](Item* i) {
            if (i->collected || i->position.y > GetScreenHeight() + 50) { delete i; return true; }
            return false;
        }), hiddenItems.end());
}

void ItemManager::Draw() {
    for (auto item : items)
        item->draw();
}

void ItemManager::DrawHiddenItem() {
    for (auto item : hiddenItems)
        item->draw();
}
void ItemManager::clearItems() {
    for (auto& item : items) {
        delete item;
    }
    for (auto& item: hiddenItems){
        delete item;
    }
    hiddenItems.clear();
    items.clear();
}

vector<Item*> ItemManager::getItems() const{
    vector<Item*> allItems;
    for(auto& item: items){
        allItems.push_back(item);
    }
    for(auto& item: hiddenItems){
        allItems.push_back(item);
    }
    return allItems;
}
