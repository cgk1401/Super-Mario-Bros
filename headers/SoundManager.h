#pragma once
#include <raylib.h>
#include <unordered_map>
using namespace std;

template <typename T>
class Singleton;

enum class SoundType {
    JUMP,
    COIN,
    POWERUP,
    DIE,
    BRICK_BREAK, 
    ONEUP,
    BOWSERFALL,
	ITEMCOLLECT,
	HURRYUP,
	FIREBALL,
	FLAGPOLE,
    PIPEDOWN,
    STOMP_AND_SWIM,
    KICKKILL,
    BUMP,
    JUMP_SMALL,
    FIRE,
    BILL_FIREWORK,
    PAUSE,
    GAMEOVER1,
    GAMEOVER2,
    BEEP,
};

enum class MusicType {
    MAIN_THEME_OVERWORLD,
    MAIN_THEME_UNDERGROUND,
    MAIN_THEME_CASTLE,
    MAIN_THEME_UNDERWATER,
    LEVEL_COMPLETE,
    WORLD_CLEAR,
    CASTLE_COMPLETE,
    ENDING,
    HURRY_UNDERGROUND,
    HURRY_OVERWORLD,
    HURRY_CASTLE,
    HURRY_UNDERWATER,
    STARMAN,
};

class SoundManager {
    template <typename T>
    friend class Singleton;
private:
    unordered_map<SoundType, Sound> sounds;
    unordered_map<MusicType, Music> musics;
    MusicType currentMusicType;
    bool musicPlaying = false;

    SoundManager();
    ~SoundManager();

public:

    void load();     // load tất cả sound/music
    void unload();   // cleanup tất cả

    void play(SoundType type);
    void playMusic(MusicType type, bool loop = true);
    void stopMusic();
    void updateMusic(); // gọi mỗi frame!
    Sound getSound(SoundType type);
    Music getMusic(MusicType type);
};
