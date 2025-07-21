#include "GamePlayer.h"
#include "Engine.h"
#include "Input/Input System.h"

void Player::Update(float deltaTime)
{
	float sped = 200;

	viper::vec2 direction{ 0, 0 };

	if (viper::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_UP)) {
		direction.y -= 1;
	}


	if (viper::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_LEFT)) {
		direction.x -= 1;
	}

	if (viper::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_RIGHT)) {
		direction.x += 1;
	}

	if (viper::GetEngine().GetInputSystem().GetKeyDown(SDL_SCANCODE_DOWN)) {
		direction.y += 1;
	}

	if (direction.LengthSqr() > 0) {
		direction = direction.Normalized();
		m_transform.position += direction * sped * deltaTime;

	}

}