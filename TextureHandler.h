#pragma once
#include "SFML/Graphics.hpp"
#include <unordered_map>
#include <string>
using std::unordered_map;
using std::string;

class TextureHandler
{
	static unordered_map <string, sf::Texture> textures;
public:
	static void AllTextures();
	static void LoadTexture(string filename);
	static sf::Texture& GetTexture(string key);
	static void Clear();
};