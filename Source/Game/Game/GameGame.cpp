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
#include "Renderer/Particle System.h"


#include <vector>


bool SpaceGame::Initialize()
{
	m_scene = std::make_unique<viper::Scene>(this);

	m_titlefont = std::make_shared<viper::Font>();
	m_titlefont->Load("Assets/bsde.ttf", 128.0f);

	m_uifont = std::make_shared<viper::Font>();
	m_uifont->Load("Assets/fonty.ttf", 40.0f);

	m_titleText = std::make_unique<viper::Text>(m_titlefont);
	m_titleText->Create(viper::GetEngine().GetRenderer(), "Space Game", viper::vec3{ 1.0f, 1.0f, 1.0f });

	m_scoreText = std::make_unique<viper::Text>(m_uifont);
	m_scoreText->Create(viper::GetEngine().GetRenderer(), "Score: 0", viper::vec3{ 1.0f, 1.0f, 1.0f });

	m_livesText = std::make_unique<viper::Text>(m_uifont);
	m_livesText->Create(viper::GetEngine().GetRenderer(), "Lives: 3", viper::vec3{ 1.0f, 1.0f, 1.0f });

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
		m_scene->RemoveAllActors();
		std::shared_ptr<viper::Model> pl_model = std::make_shared<viper::Model>(GameData::pl_points, viper::vec3{ 0, 0, 1.0f });

		viper::Transform transform{ viper::vec2{viper::GetEngine().GetRenderer().GetWidth() * .5f,viper::GetEngine().GetRenderer().GetHeight() * .5f}, 0, 5.0f };
		auto player = std::make_unique<Player>(transform, pl_model);
		player->damping = 0.5f;
		player->accel = 400.0f;
		player->angularVel = 120.0f;
		player->name = "Player";  
		player->tag = "player";
		m_scene->AddActor(std::move(player));

		m_gameState = GameState::Game;

	}
		break;
	case GameState::Game:
		m_enemySpawnTimer -= dt;
		if (m_enemySpawnTimer <= 0.0f) {
			m_enemySpawnTimer = viper::random::getReal() * 2.0f + 1.0f; // Random spawn time between 1 and 3 seconds
			SpawnEnemy();
		}
		break;
	case GameState::PlayerDeath:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0.0f) {
			m_lives--;
			if (m_lives <= 0) {
				m_gameState = GameState::GameEnd;
				m_stateTimer = 3.0f; 
			}
			else {
				m_gameState = GameState::StartRound;
			}
		}

		break;
	case GameState::GameEnd:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0.0f) {
			m_gameState = GameState::Title;
			m_score = 0; // Reset score
		}
		break;
	default:
		break;
	}
}

void SpaceGame::Draw(viper::Renderer& renderer)
{
	if (m_gameState == GameState::Title) {

		m_titleText->Create(renderer, "Space Game", viper::vec3{ 1.0f, 1.0f, 1.0f });
		m_titleText->Draw(renderer, (float)renderer.GetWidth() * .25f, (float)renderer.GetHeight() * .1f);
	}

	if (m_gameState == GameState::GameEnd) {
		m_titleText->Create(renderer, "Game Over", viper::vec3{ 1.0f, 0.0f, 0.0f });
		m_titleText->Draw(renderer, (float)renderer.GetWidth() * .3f, (float)renderer.GetHeight() * .1f);
	}
	
	if (m_gameState == GameState::Game || m_gameState == GameState::PlayerDeath || m_gameState == GameState::PlayerDeath) {
		m_scoreText->Create(renderer, "Score: " + std::to_string(m_score), viper::vec3{ 1.0f, 1.0f, 1.0f });
		m_scoreText->Draw(renderer, (float)renderer.GetWidth() * .01f, (float)renderer.GetHeight() * .01f);

		m_livesText->Create(renderer, "Lives: " + std::to_string(m_lives), viper::vec3{ 1.0f, 1.0f, 1.0f });
		m_livesText->Draw(renderer, (float)renderer.GetWidth() * .01f, (float)renderer.GetHeight() * .05f);

	}

	m_scene->Draw(renderer);

	viper::GetEngine().GetParticleSystem().Draw(renderer);
}

void SpaceGame::OnPlayerDeath()
{
	m_gameState = GameState::PlayerDeath;
	m_stateTimer = 2.0f;
}

void SpaceGame::SpawnEnemy() {
	Player* player = m_scene->GetActorByName<Player>("Player");
	if (player) {
		std::shared_ptr<viper::Model> en_model = std::make_shared<viper::Model>(GameData::en_points, viper::vec3{ 1.0f, 0, 0 });

		viper::vec2 position = player->transform.position + viper::random::onUnitCircle() * viper::random::getReal(200.0f, 500.0f);
		viper::Transform transform{ position, viper::random::getReal(0.0f, 360.0f), 4.5f};


		std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform, en_model);
		enemy->damping = 0.5f;
		enemy->accel = (viper::random::getReal() * 200.0f) + 50.0f;
		enemy->name = "Enemy";
		enemy->tag = "enemy";
		m_scene->AddActor(std::move(enemy));

	}


}
