#include "../headers/Mushroom.h"
#include "../headers/Star.h"
#include "../headers/Flower.h"

template <typename T>
class Singleton;

class ItemManager {
    template <typename T>
    friend class Singleton;
private:
    Texture texture;
    vector<Item*> items;

    Animation mushroomAni;
    Animation flowerAni;
    Animation starAni;
    Animation coinAni;
    
    ItemManager();
    ~ItemManager();
public:
    void Spawn(ItemType type, Vector2 position);
    void Update(float dt, Character* player, Map* map);
    void Draw();
    void clearItems();
    
};
