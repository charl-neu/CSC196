#include "GameGame.h"
#include "Math/Vector2.h"
#include "Renderer/Model.h"
#include "Game/Scene.h"
#include "Core/Random.h"
#include "GamePlayer.h"

#include <vector>

bool SpaceGame::Initialize()
{
	m_scene = std::make_unique<viper::Scene>();

	std::vector<viper::vec2> points{
		{-4,-4},
		{4,0},
		{-4,4},
		{-2,0},
		{-4, -4}
	};

	std::shared_ptr<class viper::Model> m_model = std::make_shared<viper::Model>(points, viper::vec3{ 0, 0, 1 });

	for (int i = 0; i < 10; i++)
	{
		viper::Transform transform{ viper::vec2{viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024}, 0, 1.0f };
		m_scene->AddActor(std::make_unique<Player>(transform, m_model));
	}

	return true;
}

void SpaceGame::Shutdown()
{
}

void SpaceGame::Update()
{
}

void SpaceGame::Draw()
{
}
