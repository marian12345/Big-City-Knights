#include "string"
#include "SDL_mixer.h"
#include "array"

class Mixer {
private:
	static Mixer* mixer;
	Mixer();
	std::array<Mix_Chunk*, 10> sound_effects;
	int music_channel1;
	int music_channel2;
public:
	static Mixer* getInstance();
	void play(int sound);
	void playMusic(int music);
	bool loadMedia();
	~Mixer();
	enum mix_chunks {BOTTLE_SHATTERING, SWING, HURT, SWORDDRAWN1, SWORDDRAWN2, BLOCK, 
		JUMP, FIGHTSONG, LOBBYSONG, DYING};
};
