#include "../headers/SoundManager.h"

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
	sounds[SoundType::BRICK_BREAK] = LoadSound("../assets/sfx/brick.wav");
	sounds[SoundType::POWERUP] = LoadSound("../assets/sfx/powerup.wav");
	sounds[SoundType::ONEUP] = LoadSound("../assets/sfx/1up.wav");
	sounds[SoundType::BOWSERFALL] = LoadSound("../assets/sfx/bowserfall.wav");
	sounds[SoundType::ITEMCOLLECT] = LoadSound("../assets/sfx/item.wav");
	sounds[SoundType::HURRYUP] = LoadSound("../assets/sfx/hurryup.wav");
	sounds[SoundType::FIREBALL] = LoadSound("../assets/sfx/fireball.wav");
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


    // Music
     musics[MusicType::MAIN_THEME_OVERWORLD] = LoadMusicStream("../assets/music/DEFAULT_OVERWORLD_THEME.mp3");
	 musics[MusicType::MAIN_THEME_UNDERGROUND] = LoadMusicStream("../assets/music/DEFAULT_UNDERGROUND_THEME.mp3");
	 musics[MusicType::MAIN_THEME_CASTLE] = LoadMusicStream("../assets/music/DEFAULT_CASTLE_THEME.mp3");
	 musics[MusicType::MAIN_THEME_UNDERWATER] = LoadMusicStream("../assets/music/DEFAULT_UNDERWATER_THEME.mp3");
	 musics[MusicType::LEVEL_COMPLETE] = LoadMusicStream("../assets/music/LEVEL_COMPLETE.mp3");
     musics[MusicType::WORLD_CLEAR] = LoadMusicStream("../assets/music/WORLD_CLEAR.mp3");
     musics[MusicType::CASTLE_COMPLETE] = LoadMusicStream("../assets/music/CASTLE_COMPLETE.mp3");
	 musics[MusicType::ENDING] = LoadMusicStream("../assets/music/ENDING.mp3");
	 musics[MusicType::HURRY_UNDERGROUND] = LoadMusicStream("../assets/music/HURRY_UNDERGROUND.mp3");
	 musics[MusicType::HURRY_OVERWORLD] = LoadMusicStream("../assets/music/HURRY_OVERWORLD.mp3");
	 musics[MusicType::HURRY_CASTLE] = LoadMusicStream("../assets/music/HURRY_CASTLE.mp3");
	 musics[MusicType::HURRY_UNDERWATER] = LoadMusicStream("../assets/music/HURRY_UNDERWATER.mp3");
     musics[MusicType::STARMAN] = LoadMusicStream("../assets/music/Starman.mp3");

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

Sound SoundManager::getSound(SoundType type) {
    return sounds[type];
}

Music SoundManager::getMusic(MusicType type) {
    return musics[type];
}
