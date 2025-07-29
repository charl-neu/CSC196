#include "GamePlayer.h"
#include "Engine.h"
#include "Input/Input System.h"
#include "Math/Math.h"

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
		
	}


	Actor::Update(deltaTime);


}