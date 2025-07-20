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


    std::vector<viper::vec2> points{
        {-5,-5},
        {5,-5},
        {5,5},
        {-5,5},
        {-5, -5}
    };

	viper::Model* model = new viper::Model{ points, {0, 0, 1} };
	
	std::vector<viper::Actor> actors;

    for (int i = 0; i < 10; i++)
    {
        
		viper::Transform transform{ viper::vec2{viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024}, viper::random::getRandomFloat() * viper::twopi, 1.0f };
        viper::Actor actr{ transform, model };
		actors.push_back(actr);
	}


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

        if (input.GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

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

        float sped = 200;

		viper::vec2 direction{ 0, 0 };

        /*
        if (input.GetKeyDown(SDL_SCANCODE_A)) {
            transform.rotation -= viper::DegToRad(10 * time.GetDeltatime());
		}

        if (input.GetKeyDown(SDL_SCANCODE_D)) {
            transform.rotation += 10 * time.GetDeltatime();
        }
        */

        if (input.GetKeyDown(SDL_SCANCODE_UP)) {
			direction.y -= 1;
		}

		

        if (direction.LengthSqr() > 0) {
            direction = direction.Normalized();
            for (auto& actor : actors) {
                actor.GetTransform().position += (direction * sped) * time.GetDeltatime();
            }
            //for (auto actor : actors) {
            //    actor.GetTransform().position += (direction * sped) * time.GetDeltatime();
			//}
		}
        

        //Draw!
		viper::vec3 color{ 1, 1, 1 };
        
        renderer.SetColor(0.0f, 0.0f, 0.0f);
        renderer.Clear();

        for (auto actor : actors) {
            actor.Update(time.GetDeltatime());
		}

		//actor.Draw(renderer, viper::vec2{ 640, 512 }, time.GetTime(), 100);
		for (auto & actr : actors)
        {   
            actr.GetTransform().rotation += 0.01f * time.GetDeltatime();
            actr.GetTransform().scale = 1 + (0.5f * sinf(time.GetTime() * 2));
            actr.Draw(renderer);
		}
       

       
        viper::vec2 speed{ 150, 200 };
        float length = speed.Length();

        for (auto& star : stars) {
            star += speed * time.GetDeltatime();
            if (star.x >= 1280) star[0] = 0;
            if (star.x < 0) star[0] = 1280;
            if (star.y >= 1024) star[1] = 0;
            if (star.y < 0) star[1] = 1024;
            renderer.SetColor((float)viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256));
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