#include "Mixer.h"

Mixer* Mixer::mixer = NULL;

Mixer::Mixer() {
	for (int i = 0; i < sound_effects.size(); i++) {
		sound_effects[i] = NULL;
	}
	music_channel1 = -1;
	music_channel2 = -1;
};

Mixer* Mixer::getInstance() {
	if (mixer == NULL) {
		mixer = new Mixer();
	}
	return mixer;
};

void Mixer::play(int sound) {
	if((sound != FIGHTSONG) && (sound != LOBBYSONG))
		Mix_PlayChannel(-1, sound_effects[sound], 0);
};

bool Mixer::loadMedia() {
	bool success = true;

	//Create paths
	std::array<std::string, 10> paths = { "assets/sounds/bottle_shattering.wav",
										"assets/sounds/short_swing_motion.wav",
										"assets/sounds/hurt.wav", 
										"assets/sounds/sword_drawn1.wav",
										"assets/sounds/sword_drawn2.wav",
										"assets/sounds/block.wav",
										"assets/sounds/jump.wav",
										"assets/sounds/bg_music.wav", 
										"assets/sounds/lobby_song.wav",
										"assets/sounds/dying.wav" };

	//Check if the arrays have the same size
	if (paths.size() != sound_effects.size()) {
		printf("Unable to load sound effects\n");
		printf("WARNING: mixer::paths.size() != mixer::sound_effects.size()\n");
		success = false;
	}
	else {
		//Load Sounds
		for (int i = 0; i < paths.size(); i++) {
			sound_effects[i] = Mix_LoadWAV(paths[i].c_str());
			if (sound_effects[i] == NULL) {
				printf("Unable to load sound effect. SDL_mixer Error: %s\n", Mix_GetError());
				success = false;
			}
		}
	}

	music_channel1 = Mix_PlayChannel(-1, sound_effects[FIGHTSONG], -1);
	Mix_Pause(music_channel1);
	music_channel2 = Mix_PlayChannel(-1, sound_effects[LOBBYSONG], -1);
	return success;
};

void Mixer::playMusic(int music) {
	if ((music == FIGHTSONG) || (music == LOBBYSONG)) {
		//If already playing and not paused - pause
		if ((Mix_Playing(music_channel1) == 1) && (Mix_Paused(music_channel1) == 0)) {
			Mix_Pause(music_channel1);
			if (Mix_Paused(music_channel2) == 1) {
				Mix_Resume(music_channel2);
			}
		}
		//If LOBBYSONG is playing, pause and play MUSIC
		else if ((Mix_Playing(music_channel2) == 1) && (Mix_Paused(music_channel2) == 0)) {
			Mix_Pause(music_channel2);					
			//If MUSIC is stopped, resume. Else play MUSIC
			if (Mix_Paused(music_channel1) == 1) {
				Mix_Resume(music_channel1);
			}
		}
	}
};

Mixer::~Mixer() {
	//Destroy sound effects
	for (int i = 0; i < sound_effects.size(); i++) {
		Mix_FreeChunk(sound_effects[i]);
		sound_effects[i] = NULL;
	}
}