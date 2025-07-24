#include "../headers/Item.h"
#include "../headers/Mushroom.h"
#include "../headers/Star.h"
#include "../headers/Flower.h"

template <typename T>
class Singleton;
enum class ItemType {
    NONE = 0,
    COIN = 1,
    MUSHROOM = 2,
    FLOWER = 3,
    STAR = 4    
};

class ItemManager {
    template <typename T>
    friend class Singleton;
private:
    Texture texture;
    vector<Item*> items;

    Animation mushroomAni;
    Animation flowerAni;
    Animation starAni;

    ItemManager();
    ~ItemManager();
public:
    void Spawn(ItemType type, Vector2 position);
    void Update(float dt, Character* player, Map* map);
    void Draw();
    void clearItems();
    
};
