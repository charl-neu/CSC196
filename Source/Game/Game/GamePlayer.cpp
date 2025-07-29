#include "GamePlayer.h"
#include "Rocket.h"
#include "Engine.h"
#include "Input/Input System.h"
#include "Math/Math.h"
#include "Game/Scene.h"
#include "Renderer/Model.h"
#include "GameData.h"
#include "Renderer/Renderer.h"

void Player::Update(float deltaTime)
{


	float rotate = 0;
	

	if (viper::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_A)) {
		rotate = -1;
	}

	if (viper::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_D)) {
		rotate = 1;
	}

	transform.rotation += rotate * deltaTime * angularVel;



	float thrust = 0;
	if (viper::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_W)) {
		thrust = 1;
	}
	if (viper::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_S)) {
		thrust = -.5;
	}


	viper::vec2 direction{ 1, 0 };
	viper::vec2 force = direction.Rotate(viper::DegToRad(transform.rotation)) * accel;
	velocity += force * thrust * deltaTime;

	transform.position.x = viper::Wrap(transform.position.x, 0.0f, 1280.0f);
	transform.position.y = viper::Wrap(transform.position.y, 0.0f, 1024.0f);

	if (viper::GetEngine().GetInputSystem().GetKeyPressed(SDL_SCANCODE_SPACE)) {
		if(firetimer <= 0.0f) {
			std::shared_ptr<viper::Model> ro_model = std::make_shared<viper::Model>(GameData::ro_points, viper::vec3{ 0, 1.0f, 0 });

			viper::Transform shape{ viper::vec2{transform.position.x, transform.position.y}, transform.rotation, 2.5f };
			auto rocket = std::make_unique<Rocket>(shape, ro_model);
			rocket->accel = 600.0f;
			rocket->damping = 0.0f;
			rocket->name = "rocket";
			rocket->tag = "rocket";
			rocket->lifespan = 1.5f;
			scene->AddActor(std::move(rocket));
			firetimer = 0.2f;
		}
	}

	firetimer -= deltaTime;

	Actor::Update(deltaTime);


}

void Player::onCollision(Actor* other)
{
	if (other->tag == "enemy") {
		destroyed = true; // Destroy the player
	}
	
}