#pragma once
#include "../Math/Transform.h"
#include "../Renderer/Model.h"


namespace viper {
	class Actor {
	public:
		Actor() = default;
		Actor(Transform transform, class Model* model) : m_transform(transform), m_model{ model } {}

		void Update(float deltaTime);
		void Draw(class Renderer& renderer);
		Transform& GetTransform() { return m_transform; }

	private:
		Transform m_transform{ {0, 0}, 0, 1 };
		Model* m_model;
	};
}