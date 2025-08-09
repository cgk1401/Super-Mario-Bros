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
    BOWSERFIREBALL,
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
    HOVER_BUTTON,
    CLICK_BUTTON,
    TELEPORT,
    SCREAM,
    FOOTSTEP,
    SURPRISE_SFX,
    lEVEL_COMPLETE,
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
    MENU_,
};

class SoundManager {
    template <typename T>
    friend class Singleton;
private:
    float musicPlayTime = 0.0f;
    unordered_map<SoundType, Sound> sounds;
    unordered_map<MusicType, Music> musics;
    MusicType currentMusicType;
    bool musicPlaying = false;

    float musicVolume;
    float soundVolume;

    SoundManager();
    ~SoundManager();

public:

    void load();     // load tất cả sound/music
    void unload();   // cleanup tất cả

    void play(SoundType type);
    void stopSound(SoundType type);
    void stopAllSounds();
    void playMusic(MusicType type, bool loop = true);
    void stopMusic();
    void updateMusic(float dt);
    void continueMusic();
    Sound getSound(SoundType type);
    MusicType getCurrentMusicType();
    Music getCurrentMusic();
    float getMusicPlayTime();
    float getmusicVolume();
    float getsoundVolume();
    void setvaluemusicVolume(float value);
    void setvaluesoundVolume(float value);

    void setMusicPlayTime(float _musicPlayTime);
    void setmusicVolume();
    void setsoundVolume();
};
