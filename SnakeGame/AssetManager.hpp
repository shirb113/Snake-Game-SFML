#pragma once

#include<map>
#include<memory>
#include<string>

#include<SFML/Graphics/Texture.hpp>
#include<SFML/Graphics/Font.hpp>

namespace Engine {

	class AssetManager
	{
	private:
		using TextureUniquePtr = std::unique_ptr<sf::Texture>;
		using FontUniquePtr = std::unique_ptr<sf::Font>;

	public:
		explicit AssetManager() = default;
		~AssetManager() = default;

	public:
		void AddTexture(const int id, const std::string& file_path, const bool repeated = false);
		void AddFont(const int id, const std::string& file_path);
		
		const sf::Texture& GetTexture(const int id) const;
		const sf::Font& GetFont(const int id) const;

	private:
		std::map<int, TextureUniquePtr> _textures;
		std::map<int, FontUniquePtr> _fonts;
	};



}