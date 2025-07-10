#include "../headers/ItemManager.h"
#include "../headers/TextureManager.h"
#include "../headers/Collision.h"

ItemManager* ItemManager::instance = nullptr;

ItemManager::ItemManager(){
    texture = TextureManager::get().load(TextureType::ITEM);

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
}

ItemManager::~ItemManager() {
    for (auto i : items) delete i;
    items.clear();  
}

void ItemManager::Spawn(ItemType type, Vector2 position) {
    Item* item = nullptr;
    switch (type) {
        case ItemType::MUSHROOM:
            item = new Mushroom(position, mushroomAni); break;
        case ItemType::FLOWER:
            item = new Flower(position, flowerAni); break;
        case ItemType::STAR:
            item = new Star(position, starAni); break;
    }
    if (item) items.push_back(item);
}

void ItemManager::Update(float dt, Character* player, Map* map) {
    for (auto item : items) {
        item->Update(dt);

        Rectangle itemRect = item->getBound();
        Rectangle marioBound = player->getBound();
        if (!item->collected && CheckCollisionRecs(itemRect, marioBound)) {
            item->OnCollected(player);
        }

        Mushroom* m = dynamic_cast<Mushroom*>(item);
        if (m) {
            Collision::handleMushroomCollisionMap(m, map);
        }

        Star* s = dynamic_cast<Star*>(item);
        if(s)
            Collision::handleStarCollision(s, map);
    }

    // Erase collected items
    items.erase(remove_if(items.begin(), items.end(),
        [](Item* i) {
            if (i->collected || i->position.y > GetScreenHeight() + 50) { delete i; return true; }
            return false;
        }), items.end());
}

void ItemManager::Draw() {
    for (auto item : items)
        item->Draw(texture);
}

void ItemManager::clearItems() {
    for (auto item : items) {
        delete item;
    }
    items.clear();
}