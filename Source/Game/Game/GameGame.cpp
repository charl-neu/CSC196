#include "GameGame.h"
#include "Math/Vector2.h"
#include "Renderer/Model.h"
#include "Game/Scene.h"
#include "Core/Random.h"
#include "GamePlayer.h"
#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Input/Input System.h"
#include "Enemy.h"
#include "GameData.h"

#include <vector>


bool SpaceGame::Initialize()
{
	m_scene = std::make_unique<viper::Scene>();

	return true;
}

void SpaceGame::Shutdown()
{
}

void SpaceGame::Update(float dt)
{
	m_scene->Update(viper::GetEngine().GetTime().GetDeltatime());
	switch (m_gameState)
	{
	case GameState::Initialize:
		m_gameState = GameState::Title;
		break;
	case GameState::Title:
		if (viper::GetEngine().GetInputSystem().GetKeyPressed(SDL_SCANCODE_SPACE)) {
			m_gameState = GameState::StartGame;
		}
		break;
	case GameState::StartGame:
		{
		m_scene->RemoveAllActors();
		m_lives = 3;
		m_gameState = GameState::StartRound;
		}
		break;
	case GameState::StartRound:
	{
		std::shared_ptr<viper::Model> pl_model = std::make_shared<viper::Model>(GameData::pl_points, viper::vec3{ 0, 0, 1.0f });

		viper::Transform transform{ viper::vec2{viper::GetEngine().GetRenderer().GetWidth() * .5f,viper::GetEngine().GetRenderer().GetHeight() * .5f}, 0, 5.0f };
		std::unique_ptr<Player> player = std::make_unique<Player>(transform, pl_model);
		player->damping = 0.5f;
		player->accel = 400.0f;
		player->angularVel = 120.0f;
		player->name = "Player";  // Set the name of the player actor
		player->tag = "player";
		m_scene->AddActor(std::move(player));

		m_gameState = GameState::Game;

	}
		break;
	case GameState::Game:
		m_enemySpawnTimer -= dt;
		if (m_enemySpawnTimer <= 0.0f) {
			m_enemySpawnTimer = viper::random::getRandomFloat() * 2.0f + 1.0f; // Random spawn time between 1 and 3 seconds
			std::shared_ptr<viper::Model> en_model = std::make_shared<viper::Model>(GameData::en_points, viper::vec3{ 1.0f, 0, 0 });
			viper::Transform transform{ viper::vec2{ viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024 }, 0, 2.0f };
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform, en_model);
			enemy->damping = 0.5f;
			enemy->accel = (viper::random::getRandomFloat() * 200.0f) + 50.0f;
			enemy->name = "Enemy"; // Set a unique name for the enemy actor
			enemy->tag = "enemy";
			m_scene->AddActor(std::move(enemy));
		}
		break;
	case GameState::PlayerDeath:
		m_lives--;
		if (m_lives <= 0) {
			m_gameState = GameState::GameEnd;
		}
		else {
			m_gameState = GameState::StartRound;
		}
		break;
	case GameState::GameEnd:
		break;
	default:
		break;
	}
}

void SpaceGame::Draw()
{
	m_scene->Draw(viper::GetEngine().GetRenderer());
}
