#include "CUTSCENES/Cutscene.h"
#include "CUTSCENES/CutSceneManager.h"


CutsceneManager::CutsceneManager(){
    skip_button = new Button("", screenWidth, screenHeight * 0.88f, screenWidth * 0.23f, screenHeight * 0.25f * 0.5f, "SKIP", WHITE, 35);
}

CutsceneManager::~CutsceneManager() {
    for(auto& scene: cutscenes)
        if (scene) delete scene;
    cutscenes.clear();
}

void CutsceneManager::play(Cutscene* cutscene) {
    cutscenes.push_back(cutscene);
    time.start(2);
}

void CutsceneManager::update(float dt) {
    if(time.isRunning()) {
        time.update(dt);
    }
    else if(time.isFinished()){
        float posX = skip_button->getBounds().x;
        float posY = skip_button->getBounds().y;
        posX = lerp(posX, screenWidth * 0.8f, dt * 2);
        skip_button->updatePos({posX, posY});
        if(skip_button->IsClicked()){
            for(auto& scene: cutscenes)
                scene->setFinish();
            Singleton<SoundManager>::getInstance().stopAllSounds();
        }
        skip_button->update(dt);
    }
    if (!cutscenes.empty()) {
    Cutscene* scene = cutscenes.front(); 

    if (scene) {
        scene->update(dt);
        if (scene->isFinished()) {
            delete scene;
            cutscenes[0] = nullptr;
            cutscenes.erase(cutscenes.begin());
        }
    }
}

}

void CutsceneManager::draw() {
    if (cutscenes.empty() == false) {
        auto& scene = cutscenes[0];
        if (scene) {
            scene->draw();
        }
    }
    skip_button->draw();
}

bool CutsceneManager::isActive() const {
    return cutscenes.empty() == false;
}

