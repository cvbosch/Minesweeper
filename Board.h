#pragma once
#include "SFML/Graphics.hpp"
#include "Random.h"
#include "TextureHandler.h"


class Board 
{
	struct Tile
	{
		bool mine;
		bool revealed;
		bool flag;
		std::string key;
		std::vector<Tile*> adjacentTiles;
		sf::Sprite sprite;

		Tile(bool mine);
		sf::Texture& GetTexture();
		sf::Texture& GetTexture(std::string key);
	};
	int test;
	bool active;
	int horizontal;
	int vertical;
	int mineCount;
	int userCount;
	int flags;
	bool minesShown;
	std::string faceStatus;
	std::vector<Tile> tiles;
	sf::Sprite face;
	sf::Sprite debug;
	sf::Sprite test_1;
	sf::Sprite test_2;
	sf::Sprite test_3;
	
public:
	Board(int horizontal, int vertical, int mineCount);
	void SetBoard();
	void SetBoard(const std::vector<char>& locations);
	void SetNeighbors();
	void TestBoard(std::string filename);
	void ShowMines();
	void HideMines();
	void DrawBase(sf::RenderWindow& window, sf::Sprite& sprite);
	void Draw(sf::RenderWindow& window, sf::Sprite& sprite);
	void DrawDigits(sf::RenderWindow& window, sf::Sprite& sprite, float verticalPosition);
	void LeftMouseAction(const sf::Vector2i pos);
	void LeftMouseOnBoard(Tile& tile);
	void RightMouseAction(const sf::Vector2i pos);
	void WinTest();
};