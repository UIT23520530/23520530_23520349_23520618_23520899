#pragma once

#include <map>

#include <SFML/Graphics.hpp>

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

		void LoadTexture(std::string name, std::string fileName);
		void LoadFont(std::string name, std::string fileName);

		sf::Texture& GetTexture(std::string name);
		sf::Font& GetFont(std::string name);
	};
}