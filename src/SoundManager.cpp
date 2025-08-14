#include "../headers/SoundManager.h"
#include <iostream>

SoundManager::SoundManager() {
    musicVolume = 0.3f;
    soundVolume = 0.3f;
    load();
    setmusicVolume();
    setsoundVolume();
}

SoundManager::~SoundManager() {
    unload();
}

void SoundManager::load() {
    // Sound effects
    sounds[SoundType::JUMP] = LoadSound("../assets/sfx/jump.wav");
    sounds[SoundType::COIN] = LoadSound("../assets/sfx/coin.wav");
    sounds[SoundType::DIE] = LoadSound("../assets/sfx/death.wav");
	sounds[SoundType::BRICK_BREAK] = LoadSound("../assets/sfx/brick.wav");
	sounds[SoundType::POWERUP] = LoadSound("../assets/sfx/powerup.wav");
	sounds[SoundType::ONEUP] = LoadSound("../assets/sfx/1up.wav");
	sounds[SoundType::BOWSERFALL] = LoadSound("../assets/sfx/bowserfall.wav");
	sounds[SoundType::ITEMCOLLECT] = LoadSound("../assets/sfx/item.wav");
	sounds[SoundType::HURRYUP] = LoadSound("../assets/sfx/hurryup.wav");
	sounds[SoundType::FIREBALL] = LoadSound("../assets/sfx/fireball.wav");
    sounds[SoundType::BOWSERFIREBALL] = LoadSound("../assets/sfx/bowserfire.wav");
	sounds[SoundType::FLAGPOLE] = LoadSound("../assets/sfx/flagpole.wav");
	sounds[SoundType::PIPEDOWN] = LoadSound("../assets/sfx/pipepowerdown.wav");
    sounds[SoundType::STOMP_AND_SWIM] = LoadSound("../assets/sfx/stompswim.wav");
	sounds[SoundType::KICKKILL] = LoadSound("../assets/sfx/kickkill.wav");
	sounds[SoundType::BUMP] = LoadSound("../assets/sfx/bump.wav");
	sounds[SoundType::JUMP_SMALL] = LoadSound("../assets/sfx/jumpsmall.wav");
	sounds[SoundType::FIRE] = LoadSound("../assets/sfx/fire.wav");
	sounds[SoundType::BILL_FIREWORK] = LoadSound("../assets/sfx/billfirework.wav");
	sounds[SoundType::PAUSE] = LoadSound("../assets/sfx/pause.wav");
	sounds[SoundType::GAMEOVER1] = LoadSound("../assets/sfx/gameover.wav");
	sounds[SoundType::GAMEOVER2] = LoadSound("../assets/sfx/gameover2.wav");
	sounds[SoundType::BEEP] = LoadSound("../assets/sfx/beep.wav");
    sounds[SoundType::HOVER_BUTTON] = LoadSound("../assets/GUI/sound/hover_sfx.mp3");
    sounds[SoundType::CLICK_BUTTON] = LoadSound("../assets/GUI/sound/button-click.mp3");
    sounds[SoundType::TELEPORT] = LoadSound("../assets/Cutscene/Kidnap/teleport.mp3");
    sounds[SoundType::FOOTSTEP] = LoadSound("../assets/Cutscene/Kidnap/footsteps-male.mp3");
    sounds[SoundType::SCREAM] = LoadSound("../assets/Cutscene/Kidnap/scream.mp3");
    sounds[SoundType::SURPRISE_SFX] = LoadSound("../assets/Cutscene/Kidnap/surprise-sound.mp3");
    sounds[SoundType::lEVEL_COMPLETE] = LoadSound("../assets/sfx/level_complete.mp3");
    sounds[SoundType::PRINCESS_KISS] = LoadSound("../assets/Cutscene/PrincessSaved/kisses.mp3");
    sounds[SoundType::DRAMATIC_CINEMA_GLITCH] = LoadSound("../assets/Cutscene/PrincessSaved/drammatic-cinematic-glitch.mp3");
    sounds[SoundType::FAR_BOOM] = LoadSound("../assets/Cutscene/PrincessSaved/far boom.mp3");
    sounds[SoundType::WHOOSH] = LoadSound("../assets/Cutscene/PrincessSaved/whoosh.mp3");
    
    // Music
     musics[MusicType::MAIN_THEME_OVERWORLD] = LoadMusicStream("../assets/music/Mario/DEFAULT_OVERWORLD_THEME.mp3");
	 musics[MusicType::MAIN_THEME_UNDERGROUND] = LoadMusicStream("../assets/music/Mario/DEFAULT_UNDERGROUND_THEME.mp3");
	 musics[MusicType::MAIN_THEME_CASTLE] = LoadMusicStream("../assets/music/Mario/DEFAULT_CASTLE_THEME.mp3");
	 musics[MusicType::MAIN_THEME_UNDERWATER] = LoadMusicStream("../assets/music/Mario/DEFAULT_UNDERWATER_THEME.mp3");
	 musics[MusicType::LEVEL_COMPLETE] = LoadMusicStream("../assets/music/Mario/LEVEL_COMPLETE.mp3");
     musics[MusicType::WORLD_CLEAR] = LoadMusicStream("../assets/music/Mario/WORLD_CLEAR.mp3");
     musics[MusicType::CASTLE_COMPLETE] = LoadMusicStream("../assets/music/Mario/CASTLE_COMPLETE.mp3");
	 musics[MusicType::ENDING] = LoadMusicStream("../assets/music/Mario/ENDING.mp3");
	 musics[MusicType::HURRY_UNDERGROUND] = LoadMusicStream("../assets/music/Mario/HURRY_UNDERGROUND.mp3");
	 musics[MusicType::HURRY_OVERWORLD] = LoadMusicStream("../assets/music/Mario/HURRY_OVERWORLD.mp3");
	 musics[MusicType::HURRY_CASTLE] = LoadMusicStream("../assets/music/Mario/HURRY_CASTLE.mp3");
	 musics[MusicType::HURRY_UNDERWATER] = LoadMusicStream("../assets/music/Mario/HURRY_UNDERWATER.mp3");
     musics[MusicType::STARMAN] = LoadMusicStream("../assets/music/Mario/Starman.mp3");
     musics[MusicType::MENU_] = LoadMusicStream("../assets/music/childhood_theme_music.mp3");
     musics[MusicType::CASTLE_DANCE] = LoadMusicStream("../assets/Cutscene/PrincessSaved/castle_dance.mp3");
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
void SoundManager::stopSound(SoundType type){
    if (sounds.count(type))
        StopSound(sounds[type]);
}
void SoundManager::stopAllSounds(){
    for(auto it : sounds){
        if(IsSoundPlaying(it.second)){
            StopSound(it.second);
        }
    }
}

void SoundManager::playMusic(MusicType type, bool loop) {
    if (!musics.count(type)) return;

    if (musicPlaying) stopMusic();

    currentMusicType = type;
    PlayMusicStream(musics[type]);
    musicPlaying = true;
    musicPlayTime = 0;
    
    musics[type].looping = loop;
}

void SoundManager::stopMusic() {
    if (musicPlaying && musics.count(currentMusicType)) {
        //StopMusicStream(musics[currentMusicType]);
        musicPlaying = false;
    }
}

void SoundManager::updateMusic(float dt) {
    if (musicPlaying)
    {
        UpdateMusicStream(musics[currentMusicType]);
        musicPlayTime += dt;
    }
}

void SoundManager::continueMusic() {
    if (!musicPlaying && musics.count(currentMusicType)) {    
        //PlayMusicStream(musics[currentMusicType]);
        musicPlaying = true;
    }
}

Sound SoundManager::getSound(SoundType type) {
    return sounds[type];
}

MusicType SoundManager::getCurrentMusicType() {
    return currentMusicType;
}

Music SoundManager::getCurrentMusic() {
    return musics[currentMusicType];
}
float SoundManager::getMusicPlayTime(){
    return musicPlayTime;
}


float SoundManager::getmusicVolume() {
    return this->musicVolume;
}

float SoundManager::getsoundVolume() {
    return this->soundVolume;
}

void SoundManager::setvaluemusicVolume(float value) {
    this->musicVolume = value;
}

void SoundManager::setvaluesoundVolume(float value) {
    this->soundVolume = value;
}
void SoundManager::setMusicPlayTime(float _musicPlayTime){
    musicPlayTime = _musicPlayTime;
    SeekMusicStream(getCurrentMusic(), musicPlayTime);
}

void SoundManager::setmusicVolume() {
    for (auto& it : musics) {
        SetMusicVolume(it.second, musicVolume);
    }
}

void SoundManager::setsoundVolume() {
    for (auto& it : sounds) {
        SetSoundVolume(it.second, soundVolume);
    }
}


