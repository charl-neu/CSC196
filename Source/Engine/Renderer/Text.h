#pragma once

#include "Renderer.h"
#include "Font.h"
#include "../Math/Vector3.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_ttf.h>
#include <string>

namespace viper {
	class Text {
	public:
		Text() = default;
		Text(Font* font) : m_font{ font } {}
		~Text();

		bool Create(Renderer& renderer, const std::string& text, const vec3& color);
		void Draw(Renderer& renderer, int x, int y);

	private:
		Font* m_font{ nullptr };
		SDL_Texture* m_texture{ nullptr };
	};

}