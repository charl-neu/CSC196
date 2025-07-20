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
#include "GamePlayer.h"
#include "scene.h"

#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include <memory>


int main(int argc, char* argv[]) {
    //Initialize engine systems
    viper::Time time;

	std::unique_ptr<viper::Renderer> renderer = std::make_unique<viper::Renderer>();
    renderer->Initialize();
    renderer->CreateWindow("Viper Engine", 1280, 1024);

    std::unique_ptr<viper::InputSystem> input = std::make_unique<viper::InputSystem>();
    input->Initialize();

    SDL_Event e;
    bool quit = false;

	std::unique_ptr<viper::AudioSystem> audio = std::make_unique<viper::AudioSystem>();;
	audio->Initialize();


    std::vector<viper::vec2> points{
        {-5,-5},
        {5,-5},
        {5,5},
        {-5,5},
        {-5, -5}
    };


	std::shared_ptr<viper::Model> model = std::make_shared<viper::Model>(points, viper::vec3{ 0, 0, 1 });
	//viper::Model* model = new viper::Model{ points, {0, 0, 1} };
	
	viper::Scene scene;

    for (int i = 0; i < 10; i++)
    {
        
		viper::Transform transform{ viper::vec2{viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024}, viper::random::getRandomFloat() * viper::twopi, 1.0f };
        scene.AddActor(std::make_unique<Player>(transform, model));
	}


    //create stars
    std::vector<viper::vec2> stars;
    for (int i = 0; i < 100; i++)
    {
        stars.push_back(viper::vec2{viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024});
    }
    //vec2 v(30, 40);

    //init sounds
	audio->AddSound("bass.wav", "bass");


    //main loop
    while (!quit) {
        time.Tick();
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        if (input->GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

        //update engine systems
		audio->Update();
        input->Update();

        if (input->GetKeyPressed(SDL_SCANCODE_A)) {
			audio->PlaySound("bass");
		}

        //get inputs
        if (input->GetKeyPressed(SDL_SCANCODE_A)) {
            std::cout << "pressed\n";
        }

        if (input->GetMouseButtonPressed(viper::InputSystem::MouseButton::Left)) {
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

        if (input->GetKeyDown(SDL_SCANCODE_UP)) {
			direction.y -= 1;
		}

		

        if (direction.LengthSqr() > 0) {
            direction = direction.Normalized();
            //for (auto& actor : actors) {
            //    actor->GetTransform().position += (direction * sped) * time.GetDeltatime();
            //}
            //for (auto actor : actors) {
            //    actor.GetTransform().position += (direction * sped) * time.GetDeltatime();
			//}
		}
        


        //Draw!
		viper::vec3 color{ 1, 1, 1 };
        
        renderer->SetColor(0.0f, 0.0f, 0.0f);
        renderer->Clear();

        /*
        for (auto actor : actors) {
            actor->Update(time.GetDeltatime());
		}
        */
		//actor.Draw(renderer, viper::vec2{ 640, 512 }, time.GetTime(), 100);

        scene.Draw(*renderer);

       
        viper::vec2 speed{ 150, 200 };
        float length = speed.Length();

        for (auto& star : stars) {
            star += speed * time.GetDeltatime();
            if (star.x >= 1280) star[0] = 0;
            if (star.x < 0) star[0] = 1280;
            if (star.y >= 1024) star[1] = 0;
            if (star.y < 0) star[1] = 1024;
            renderer->SetColor((float)viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256));
            renderer->DrawPoint(star.x, star.y);
        }
        //for (int i = 0; i < 100; i++) {
        //    renderer.SetColor(viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256));
        //    renderer.DrawLine(viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024, viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024);
        //    renderer.SetColor(viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256));
        //    renderer.DrawPoint(viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024);
        //}
        renderer->Present();

    }
    
	
	audio->Shutdown();
    renderer->Shutdown();
	input->Shutdown();

    return 0;
}