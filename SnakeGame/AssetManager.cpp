#include "AssetManager.hpp"

void Engine::AssetManager::AddTexture(const int id, const std::string& file_path, const bool repeated)
{
	auto texture = std::make_unique<sf::Texture>();

	if (texture->loadFromFile(file_path))
	{
		texture->setRepeated(repeated);
		_textures[id] = std::move(texture);
	}

}

void Engine::AssetManager::AddFont(const int id, const std::string& file_path)
{
	auto font = std::make_unique<sf::Font>();

	if (font->loadFromFile(file_path))
	{
		_fonts[id] = std::move(font);
	}
}

const sf::Texture& Engine::AssetManager::GetTexture(const int id) const
{
	return *(_textures.at(id).get());
}

const sf::Font& Engine::AssetManager::GetFont(const int id) const
{
	return *(_fonts.at(id).get());
}
