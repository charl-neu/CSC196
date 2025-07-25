#include "Scene.h"
#include "../Game/Actor.h"
#include "../Renderer/Renderer.h"

namespace viper
{
	/// <summary>
	/// Updates all actors by calling their Draw method with the given time delta.
	/// </summary>
	/// <param name="deltaTime">The elapsed time since the last update, in seconds.</param>
	void Scene::Update(float deltaTime) {
		for (auto& actr : m_actors)
		{
			actr->Update(deltaTime);
		}
	}

	/// <summary>
	/// Draws all actors using the provided renderer.
	/// </summary>
	/// <param name="renderer">A reference to the Renderer object used to draw the actors.</param>
	void Scene::Draw(class Renderer& renderer) {
		for (auto& actr : m_actors)
		{
			actr->Draw(renderer);
		}
	}

	/// <summary>
	/// Adds an actor to the scene by transferring ownership of the actor to the scene.
	/// </summary>
	/// <param name="actor">A unique pointer to the actor to be added. Ownership of the actor is transferred to the scene.</param>
	void Scene::AddActor(std::unique_ptr<Actor> actor) {
		m_actors.push_back(std::move(actor));
	}
}