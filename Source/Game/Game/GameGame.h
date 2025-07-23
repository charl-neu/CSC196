#pragma once
#include "Game/Game.h"
#include <memory>



class SpaceGame : public viper::Game
{

public:
	SpaceGame() = default;
	bool Initialize() override;
	void Shutdown() override;
	void Update() override;
	void Draw() override;


private:
	
};
