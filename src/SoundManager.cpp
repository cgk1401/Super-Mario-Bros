#include "../headers/SoundManager.h"

SoundManager* SoundManager::instance = nullptr;

SoundManager* SoundManager::get() {
    if (!instance)
        instance = new SoundManager();
    return instance;
}

SoundManager::SoundManager() {
    load();
}

SoundManager::~SoundManager() {
    unload();
}

void SoundManager::load() {
    // Sound effects
    sounds[SoundType::JUMP] = LoadSound("../assets/sfx/jump.wav");
    sounds[SoundType::COIN] = LoadSound("../assets/sfx/coin.wav");
    sounds[SoundType::DIE] = LoadSound("../assets/sfx/death.wav");
    //....

    // Music
    // musics[
    // ::OVERWORLD] = LoadMusicStream("../assets/music/overworld.mp3");
    // musics[MusicType::UNDERGROUND] = LoadMusicStream("../assets/music/underground.mp3");
    // musics[MusicType::BOSS] = LoadMusicStream("../assets/music/boss_theme.mp3");
    // musics[MusicType::GAME_OVER] = LoadMusicStream("../assets/music/gameover.mp3");
    //...
}

void SoundManager::unload() {
    for (auto& [_, s] : sounds) UnloadSound(s);
    sounds.clear();

    for (auto& [_, m] : musics) UnloadMusicStream(m);
    musics.clear();
}

void SoundManager::play(SoundType type) {
    if (sounds.count(type))
        PlaySound(sounds[type]);
}

void SoundManager::playMusic(MusicType type, bool loop) {
    if (!musics.count(type)) return;

    if (musicPlaying) stopMusic();

    currentMusicType = type;
    PlayMusicStream(musics[type]);
    musicPlaying = true;

    if (loop) musics[type].looping = true;
}

void SoundManager::stopMusic() {
    if (musicPlaying && musics.count(currentMusicType)) {
        StopMusicStream(musics[currentMusicType]);
        musicPlaying = false;
    }
}

void SoundManager::updateMusic() {
    if (musicPlaying)
        UpdateMusicStream(musics[currentMusicType]);
}
