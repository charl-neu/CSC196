#include "GamePlayer.h"
#include "Engine.h"
#include "Input/Input System.h"

void Player::Update(float deltaTime)
{
	float sped = 200;
	float angularVel = 90.0f; 

	float rotate = 0;
	

	if (viper::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_A)) {
		rotate = -1;
	}

	if (viper::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_D)) {
		rotate = 1;
	}

	m_transform.rotation += rotate * deltaTime * angularVel;



	float thrust = 0;
	if (viper::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_W)) {
		thrust = 1;
	}
	if (viper::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_S)) {
		thrust = -.5;
	}


	viper::vec2 direction{ 1, 0 };
	viper::vec2 force = direction.Rotate(viper::DegToRad(m_transform.rotation)) * sped;
	velocity += force * thrust * deltaTime;


	Actor::Update(deltaTime);


}