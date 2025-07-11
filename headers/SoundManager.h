#pragma once
#include <raylib.h>
#include <unordered_map>
using namespace std;

enum class SoundType {
    JUMP,
    COIN,
    POWERUP,
    DIE,
    // ... add more
};

enum class MusicType {
    OVERWORLD,
    UNDERGROUND,
    BOSS,
    GAME_OVER
};

class SoundManager {
private:
    static SoundManager* instance;
    unordered_map<SoundType, Sound> sounds;
    unordered_map<MusicType, Music> musics;
    MusicType currentMusicType;
    bool musicPlaying = false;

    SoundManager();
    ~SoundManager();

public:
    static SoundManager* get();

    void load();     // load tất cả sound/music
    void unload();   // cleanup tất cả

    void play(SoundType type);
    void playMusic(MusicType type, bool loop = true);
    void stopMusic();
    void updateMusic(); // gọi mỗi frame!
};
