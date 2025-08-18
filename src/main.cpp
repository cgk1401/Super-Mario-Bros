#include "Game.h"

int main() {
    Singleton<Game>::getInstance().run();
    return 0;
}