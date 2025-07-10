#include "../headers/Item.h"
#include "../headers/Mushroom.h"
#include "../headers/Star.h"
#include "../headers/Flower.h"

enum class ItemType {
    NONE = 0,
    COIN = 1,
    MUSHROOM = 2,
    FLOWER = 3,
    STAR = 4    
};

class ItemManager {
private:
    static ItemManager* instance;
    Texture texture;
    vector<Item*> items;

    Animation mushroomAni;
    Animation flowerAni;
    Animation starAni;
public:
    void Spawn(ItemType type, Vector2 position);
    void Update(float dt, Character* player, Map* map);
    void Draw();
    void clearItems();
    
    ItemManager();
    ~ItemManager();

    static ItemManager& get(){
        if(!instance){
            instance = new ItemManager();
        }
        return *instance;
    }
};
