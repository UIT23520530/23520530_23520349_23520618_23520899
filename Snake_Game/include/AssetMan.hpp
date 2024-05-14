#pragma once

#include <map>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

namespace Engine
{
	class AssetMan
	{
	private:
		std::map<std::string, sf::Texture> m_textures;
		std::map<std::string, sf::Font> m_fonts;
	public:
		AssetMan() {}
		~AssetMan() {}

		void LoadTexture(std::string name, std::string fileName, bool wantRepeated = false);
		void LoadFont(std::string name, std::string fileName);

		sf::Texture& GetTexture(std::string name);
		sf::Font& GetFont(std::string name);
	};
}