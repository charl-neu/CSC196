#include "Math/Math.h"
#include "Math\Vector2.h"
#include "Core/Random.h"
#include "Core/Time.h"
#include "Renderer/Renderer.h"
#include "Input/Input System.h"
#include "Audio/Audio System.h"


#include <SDL3/SDL.h>
#include <iostream>
#include <vector>


int main(int argc, char* argv[]) {
    //Initialize engine systems
    viper::Time time;

    viper::Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("Viper Engine", 1280, 1024);

    viper::InputSystem input;
    input.Initialize();

    SDL_Event e;
    bool quit = false;



	viper::AudioSystem audio;
	audio.Initialize();

    //create stars
    std::vector<viper::vec2> stars;
    for (int i = 0; i < 100; i++)
    {
        stars.push_back(viper::vec2{viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024});
    }
    //vec2 v(30, 40);

    //init sounds
	audio.AddSound("bass.wav", "bass");


    //main loop
    while (!quit) {
        time.Tick();
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        //update engine systems
		audio.Update();
        input.Update();

        if (input.GetKeyPressed(SDL_SCANCODE_A)) {
			audio.PlaySound("bass");
		}


        //get inputs
        if (input.GetKeyPressed(SDL_SCANCODE_A)) {
            std::cout << "pressed\n";
        }

        if (input.GetMouseButtonPressed(viper::InputSystem::MouseButton::Left)) {
            std::cout << "mouse pressed\n";
        }

        //viper::vec2 mouse = input.GetMousePosition();
        //std::cout << mouse.x << " " << mouse.y << std::endl;


        //Draw!
        renderer.SetColor(0, 0, 0);
        renderer.Clear();

       
        viper::vec2 speed{ 100, 200 };
        float length = speed.Length();

        for (auto& star : stars) {
            star += speed * time.GetDeltatime();
            if (star.x >= 1280) star[0] = 0;
            if (star.x < 0) star[0] = 1280;
            if (star.y >= 1024) star[1] = 0;
            if (star.y < 0) star[1] = 1024;
            renderer.SetColor(viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256));
            renderer.DrawPoint(star.x, star.y);
        }
        //for (int i = 0; i < 100; i++) {
        //    renderer.SetColor(viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256));
        //    renderer.DrawLine(viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024, viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024);
        //    renderer.SetColor(viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256));
        //    renderer.DrawPoint(viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024);
        //}
        renderer.Present();

    }
    
	audio.Shutdown();
    renderer.Shutdown();

    return 0;
}