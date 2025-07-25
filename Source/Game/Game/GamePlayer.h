#pragma once
#include "../Engine/Game/Actor.h"

class Player : public viper::Actor
{
public:
	Player() = default;
	Player(const viper::Transform& transform, std::shared_ptr<viper::Model> model) :
		Actor{ transform, model } 
	{}

	void Update(float deltaTime) override;
private:
};