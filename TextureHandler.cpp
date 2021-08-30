#include "TextureHandler.h"
using namespace std;

unordered_map <string, sf::Texture> TextureHandler::textures;

void TextureHandler::LoadTexture(string filename)
{
	string  filePath = "images/";
	filePath += filename;
	filePath += ".png";
	textures[filename].loadFromFile(filePath);
}

sf::Texture& TextureHandler::GetTexture(string key)
{
	return textures[key];
}

void TextureHandler::Clear()
{
	textures.clear();
}

void TextureHandler::AllTextures()
{
    LoadTexture("tile_revealed");
    LoadTexture("tile_hidden");
    LoadTexture("mine");
    LoadTexture("flag");
    LoadTexture("digits");
    LoadTexture("face_happy");
    LoadTexture("face_lose");
    LoadTexture("face_win");
    LoadTexture("debug");
    LoadTexture("test_1");
    LoadTexture("test_2");
    LoadTexture("test_3");
    LoadTexture("number_1");
    LoadTexture("number_2");
    LoadTexture("number_3");
    LoadTexture("number_4");
    LoadTexture("number_5");
    LoadTexture("number_6");
    LoadTexture("number_7");
    LoadTexture("number_8");
}