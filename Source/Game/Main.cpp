#include "Game/Actor.h"
#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Transform.h"
#include "Core/Random.h"
#include "Core/Time.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Input/Input System.h"
#include "Audio/Audio System.h"
#include "game/GamePlayer.h"
#include "game/scene.h"
#include "Engine.h"
#include "game/GameGame.h"


#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include <memory>

#define RENDERER viper::GetEngine().GetRenderer()
#define AUDIO viper::GetEngine().GetAudioSystem()
#define INPUT viper::GetEngine().GetInputSystem()
#define TIME viper::GetEngine().GetTime()

int main(int argc, char* argv[]) {
	

    //init engine
	viper::GetEngine().Initialize();

	std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
	game->Initialize();



    //create stars
    std::vector<viper::vec2> stars;
    for (int i = 0; i < 100; i++)
    {
        stars.push_back(viper::vec2{viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024});
    }

    //init sounds
	AUDIO.AddSound("bass.wav", "bass");


    SDL_Event e;
    bool quit = false;

    //main loop
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        //update engine systems
        viper::GetEngine().Update();
        game->Update();


        if (INPUT.GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

       
        if (INPUT.GetKeyPressed(SDL_SCANCODE_A)) {
            AUDIO.PlaySound("bass");
		}

        //get inputs
        if (INPUT.GetKeyPressed(SDL_SCANCODE_A)) {
            std::cout << "pressed\n";
        }

        if (INPUT.GetMouseButtonPressed(viper::InputSystem::MouseButton::Left)) {
            std::cout << "mouse pressed\n";
        }


		viper::vec3 color{ 1, 1, 1 };
        
        RENDERER.SetColor(0.0f, 0.0f, 0.0f);
        RENDERER.Clear();

		game->Draw();

        for(auto& star : stars)
        {
            RENDERER.SetColor(color.x, color.y, color.z);
            RENDERER.DrawPoint(star.x, star.y);
		}

        RENDERER.Present();

    }
    
	viper::GetEngine().Shutdown();
	game->Shutdown();

    return 0;
}