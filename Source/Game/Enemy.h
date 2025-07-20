#pragma once
#include "../Engine/Game/Actor.h"

class Enemy: public viper::Actor
{
public:
	Enemy() = default;
	Enemy(const viper::Transform& transform, std::shared_ptr<viper::Model> model) :
		Actor{ transform, model }
	{
	}

	void Update(float deltaTime) override;
private:
};