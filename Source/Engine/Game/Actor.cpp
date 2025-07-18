#include "Actor.h"
#include "../Renderer/Model.h"
#include "../Renderer/Renderer.h"

namespace viper {
	/// <summary>
	/// Updates the actor's state based on the elapsed time.
	/// </summary>
	/// <param name="deltaTime">The time elapsed since the last update.</param>
	void Actor::Update(float deltaTime) {

	}

	/// <summary>
	/// Draws the actor using the specified renderer.
	/// </summary>
	/// <param name="renderer">The renderer used to draw the actor.</param>
	void Actor::Draw(Renderer& renderer) {
		if (m_model) {
			m_model->Draw(renderer, m_transform);
		}
	}
} // namespace viper