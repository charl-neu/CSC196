#include <iostream>
#include <vector>
#include <fmod.hpp>

int main(int argc, char* argv[]) {
	// create audio system
	FMOD::System* audio;
	FMOD::System_Create(&audio);

	void* extradriverdata = nullptr;
	audio->init(32, FMOD_INIT_NORMAL, extradriverdata);
	
	FMOD::Sound* sound = nullptr;
	std::vector<FMOD::Sound*> sounds;

	audio->createSound("bass.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("snare.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	bool quit = false;

	while (!quit) {
		audio->update();

	}
}