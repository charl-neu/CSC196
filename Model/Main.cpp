
#include "math/vector2.h"
#include "renderer/renderer.h"
#include "renderer/model.h"
#include "game/actor.h"
#include "game/scene.h"

#include <iostream> 
#include <vector>

int main(int argc, char* argv[]) {

    std::unique_ptr<viper::Renderer> renderer = std::make_unique<viper::Renderer>();
    renderer->Initialize();
    renderer->CreateWindow("Viper Engine", 1280, 1024);

    SDL_Event e;
    bool quit = false;


    std::vector<viper::vec2> points{
    {4,-4},
    {-4,0},
    {4,4},
    {2,0},
    {4, -4}
    };


    std::shared_ptr<viper::Model> model = std::make_shared<viper::Model>(points, viper::vec3{ 0, 0, 1 });

    viper::Scene scene;
    viper::Transform transform{ viper::vec2{640, 512},viper::pi, 10.0f };
    scene.AddActor(std::make_unique<viper::Actor>(transform, model));
    

    //main loop
    while (!quit) {

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        renderer->SetColor(0.0f, 0.0f, 0.0f);
        renderer->Clear();

        scene.Draw(*renderer);

        renderer->Present();

    }

    renderer->Shutdown();

    return 0;
}