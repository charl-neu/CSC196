#include "GameGame.h"
#include "Math/Vector2.h"
#include "Renderer/Model.h"
#include "Game/Scene.h"
#include "Core/Random.h"
#include "GamePlayer.h"
#include "Engine.h"
#include "Renderer/Renderer.h"

#include <vector>

bool SpaceGame::Initialize()
{
	m_scene = std::make_unique<viper::Scene>();

	std::vector<viper::vec2> pl_points{
		{-4,-4},
		{4,0},
		{-4,4},
		{-2,0},
		{-4, -4}
	};

	std::shared_ptr<class viper::Model> pl_model = std::make_shared<viper::Model>(pl_points, viper::vec3{ 0, 0, 10 });

	viper::Transform transform{ viper::vec2{viper::GetEngine().GetRenderer().GetWidth()*.5f,viper::GetEngine().GetRenderer().GetHeight() * .5f}, 0, 5.0f};
	m_scene->AddActor(std::make_unique<Player>(transform, pl_model));

	for (int i = 0; i < 10; i++)
	{

	}

	return true;
}

void SpaceGame::Shutdown()
{
}

void SpaceGame::Update()
{
	m_scene->Update(viper::GetEngine().GetTime().GetDeltatime());
}

void SpaceGame::Draw()
{
	m_scene->Draw(viper::GetEngine().GetRenderer());
}
