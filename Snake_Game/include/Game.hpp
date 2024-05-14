#pragma once

#include <memory>
#include <string>

#include <SFML/Graphics/RenderWindow.hpp>

#include <StateMan.hpp>
#include <AssetMan.hpp>
#include <InputMan.hpp>

namespace Engine
{
	struct GameData
	{
		StateMan states;
		sf::RenderWindow window;
		AssetMan assets;
		InputMan input;
	};
	typedef std::shared_ptr<GameData> GameDataRef;
	
	class Game
	{
	private:
		const float deltaTime = 1.0f / 60.0f;
		sf::Clock m_clock;

		GameDataRef m_data = std::make_shared<GameData>();

		void Run();
	public:
		Game(int width, int height, std::string title);
	};
}