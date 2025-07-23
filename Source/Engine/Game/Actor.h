#pragma once
#include "../Math/Transform.h"
#include "../Math/Vector2.h"
#include <string>
#include <memory>

namespace viper {
	class Actor {
	public:
		std::string name;
		std::string tag;

		vec2 velocity{ 0 , 0 };
	public:
		Actor() = default;
		Actor(const Transform& transform, std::shared_ptr<class Model> model) : m_transform(transform), m_model{ model } {}

		virtual void Update(float deltaTime);
		virtual void Draw(class Renderer& renderer);

		Transform& GetTransform() { return m_transform; }

	protected:
		Transform m_transform{ {0, 0}, 0, 1 };
		std::shared_ptr<Model> m_model;
	};
}