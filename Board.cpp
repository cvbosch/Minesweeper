#include "Board.h"
#include<iostream>
#include <vector>
#include <fstream>
using namespace std;

Board::Board(int horizontal, int vertical, int mineCount)
{
    active = true;
	this->horizontal = horizontal;
	this->vertical = vertical;
	this->mineCount = mineCount;
    userCount = mineCount;
    flags = 0;
    minesShown = false;
    faceStatus = "face_happy";
    SetBoard();
}

void Board::SetBoard()
{
    tiles.clear();
    active = true;
    flags = 0;
    mineCount = userCount;
    faceStatus = "face_happy";
    
    vector<int> mineLocations;
    mineLocations.reserve(mineCount);

    int location = Random::IntRNG(0, horizontal * vertical-1);
    mineLocations.push_back(location); 
    int firstLocation = location;

    for (int i = 1; i < mineCount; i++)
    {
        location = Random::IntRNG(0, horizontal * vertical-1);
        for (unsigned int j = 0; j < mineLocations.size(); j++)
        {
            if (location == mineLocations[j] || location == firstLocation)
            {
                location = Random::IntRNG(0, horizontal * vertical -1);
                j = 0;
            }
        }
        mineLocations.push_back(location);
    }
    
    for (int i = 0; i < horizontal*vertical; i++)
    {
        bool notMine = true;
        for (unsigned int j = 0; j < mineLocations.size(); j++)
        {
            if (i == mineLocations[j])
            {
                Tile tile = Tile(true);
                tiles.push_back(tile);
                notMine = false;
                break;
            }
        }
        if (notMine)
        {
            Tile tile = Tile(false);
            tiles.push_back(tile);
        }
    }

    SetNeighbors();

    if (minesShown)
        ShowMines();
    else
        HideMines();
}

void Board::SetBoard(const vector<char>& locations)
{
    tiles.clear();
    active = true;
    flags = 0;
    mineCount = 0;
    faceStatus = "face_happy";

    for (unsigned int i = 0; i < locations.size(); i++)
    {
        if (locations[i] == '1')
        {
            Tile tile = Tile(true);
            tiles.push_back(tile);
            mineCount++;
        }
        else
        {
            Tile tile = Tile(false);
            tiles.push_back(tile);
        }
    }

    SetNeighbors();

    if (minesShown)
        ShowMines();
    else
        HideMines();
}

void Board::SetNeighbors()
{
    unsigned int index = 0;
    for (int i = 0; i < vertical; i++)
    {
        for (int j = 0; j < horizontal; j++)
        {
            if (i != 0 && i != vertical - 1 && j != 0 && j != horizontal - 1)
            {
                tiles[index].adjacentTiles.push_back(&tiles[index - horizontal + 1]);
                tiles[index].adjacentTiles.push_back(&tiles[index - horizontal]);
                tiles[index].adjacentTiles.push_back(&tiles[index - horizontal - 1]);
                tiles[index].adjacentTiles.push_back(&tiles[index - 1]);
                tiles[index].adjacentTiles.push_back(&tiles[index + 1]);
                tiles[index].adjacentTiles.push_back(&tiles[index + horizontal - 1]);
                tiles[index].adjacentTiles.push_back(&tiles[index + horizontal]);
                tiles[index].adjacentTiles.push_back(&tiles[index + horizontal + 1]);
            }
            else if (i == 0 && j == 0)
            {
                tiles[index].adjacentTiles.push_back(&tiles[index + 1]);
                tiles[index].adjacentTiles.push_back(&tiles[index + horizontal]);
                tiles[index].adjacentTiles.push_back(&tiles[index + horizontal + 1]);
            }
            else if (i == 0 && j == horizontal - 1)
            {
                tiles[index].adjacentTiles.push_back(&tiles[index - 1]);
                tiles[index].adjacentTiles.push_back(&tiles[index + horizontal - 1]);
                tiles[index].adjacentTiles.push_back(&tiles[index + horizontal]);
            }
            else if (i == vertical - 1 && j == 0)
            {
                tiles[index].adjacentTiles.push_back(&tiles[index + 1]);
                tiles[index].adjacentTiles.push_back(&tiles[index - horizontal + 1]);
                tiles[index].adjacentTiles.push_back(&tiles[index - horizontal]);
            }
            else if (i == vertical - 1 && j == horizontal - 1)
            {
                tiles[index].adjacentTiles.push_back(&tiles[index - 1]);
                tiles[index].adjacentTiles.push_back(&tiles[index - horizontal]);
                tiles[index].adjacentTiles.push_back(&tiles[index - horizontal - 1]);
            }
            else if (i == 0)
            {
                tiles[index].adjacentTiles.push_back(&tiles[index - 1]);
                tiles[index].adjacentTiles.push_back(&tiles[index + 1]);
                tiles[index].adjacentTiles.push_back(&tiles[index + horizontal - 1]);
                tiles[index].adjacentTiles.push_back(&tiles[index + horizontal]);
                tiles[index].adjacentTiles.push_back(&tiles[index + horizontal + 1]);
            }
            else if (i == vertical - 1)
            {
                tiles[index].adjacentTiles.push_back(&tiles[index - horizontal + 1]);
                tiles[index].adjacentTiles.push_back(&tiles[index - horizontal]);
                tiles[index].adjacentTiles.push_back(&tiles[index - horizontal - 1]);
                tiles[index].adjacentTiles.push_back(&tiles[index - 1]);
                tiles[index].adjacentTiles.push_back(&tiles[index + 1]);
            }
            else if (j == 0)
            {
                tiles[index].adjacentTiles.push_back(&tiles[index - horizontal + 1]);
                tiles[index].adjacentTiles.push_back(&tiles[index - horizontal]);
                tiles[index].adjacentTiles.push_back(&tiles[index + 1]);
                tiles[index].adjacentTiles.push_back(&tiles[index + horizontal]);
                tiles[index].adjacentTiles.push_back(&tiles[index + horizontal + 1]);
            }
            else if (j == horizontal - 1)
            {
                tiles[index].adjacentTiles.push_back(&tiles[index - horizontal]);
                tiles[index].adjacentTiles.push_back(&tiles[index - horizontal - 1]);
                tiles[index].adjacentTiles.push_back(&tiles[index - 1]);
                tiles[index].adjacentTiles.push_back(&tiles[index + horizontal - 1]);
                tiles[index].adjacentTiles.push_back(&tiles[index + horizontal]);
            }

            index++;
        }
    }
}

void Board::TestBoard(string filename)
{
    ifstream file(filename);
    int count = 0;
    char info = '0';
    vector<char> mines;
    while (file.get(info))
    {
        if (info == '0' || info == '1')
        {
            if (info == '1')
                count++;
            mines.push_back(info);
        }
    }
    SetBoard(mines);
}

void Board::ShowMines()
{
    for (unsigned int i = 0; i < tiles.size(); i++)
    {
        if (tiles[i].mine)
        {
            tiles[i].key = "mine";
        }
    }
}

void Board::HideMines()
{
    for (unsigned int i = 0; i < tiles.size(); i++)
    {
        if (tiles[i].mine)
        {
            if (!tiles[i].flag)
                tiles[i].key = "tile_hidden";
            else
                tiles[i].key = "flag";
        }
    }
}

void Board::DrawBase(sf::RenderWindow& window, sf::Sprite& sprite)
{
    float verticalPosition = 0.0f;
    for (int i = 0; i < vertical; i++)
    {
        float horizontalPosition = 0.0f;
        for (int j = 0; j < horizontal; j++)
        {
            sprite.setPosition(sf::Vector2f(horizontalPosition, verticalPosition));
            window.draw(sprite);
            horizontalPosition += 32.0f;
        }
        verticalPosition += 32.0f;
    }
}

void Board::Draw(sf::RenderWindow& window, sf::Sprite& sprite)
{
    auto iter = tiles.begin();

    float verticalPosition = 0.0f;
    for (int i = 0; i < vertical; i++)
    {
        float horizontalPosition = 0.0f;
        for (int j = 0; j < horizontal; j++)
        {
            if ((*iter).flag)
            {
                sprite.setTexture((*iter).GetTexture("flag"));
                sprite.setPosition(sf::Vector2f(horizontalPosition, verticalPosition));
                window.draw(sprite);
            }
            sprite.setTexture((*iter).GetTexture());
            sprite.setPosition(sf::Vector2f(horizontalPosition, verticalPosition));
            window.draw(sprite);
            (*iter).sprite = sprite;
            horizontalPosition += 32.0f;
            iter++;
        }
        verticalPosition += 32.0f;
    }
    
   
    sf::Sprite digits(TextureHandler::GetTexture("digits"));
    DrawDigits(window, digits, verticalPosition);
    
    face.setTexture(TextureHandler::GetTexture(faceStatus));
    float horizontalPosition = window.getSize().x / 2.0f - face.getTextureRect().width / 2;
    face.setPosition(sf::Vector2f(horizontalPosition, verticalPosition));
    window.draw(face);

    horizontalPosition += face.getTextureRect().width * 2;
    debug.setTexture(TextureHandler::GetTexture("debug"));
    debug.setPosition(sf::Vector2f(horizontalPosition, verticalPosition));
    window.draw(debug);

    horizontalPosition += face.getTextureRect().width;
    test_1.setTexture(TextureHandler::GetTexture("test_1"));
    test_1.setPosition(sf::Vector2f(horizontalPosition, verticalPosition));
    window.draw(test_1);

    horizontalPosition += face.getTextureRect().width;
    test_2.setTexture(TextureHandler::GetTexture("test_2"));
    test_2.setPosition(sf::Vector2f(horizontalPosition, verticalPosition));
    window.draw(test_2);

    horizontalPosition += face.getTextureRect().width;
    test_3.setTexture(TextureHandler::GetTexture("test_3"));
    test_3.setPosition(sf::Vector2f(horizontalPosition, verticalPosition));
    window.draw(test_3);
}

void Board::DrawDigits(sf::RenderWindow& window, sf::Sprite& sprite, float verticalPosition)
{
    short count = mineCount - flags;
    float horizontalPosition = 0;

    if (count < 0)
    {
        count = abs(count);
        sprite.setTextureRect(sf::IntRect(210, 0, 21, 32));
        sprite.setPosition(horizontalPosition, verticalPosition);
        window.draw(sprite);
        horizontalPosition += 21.0f;
    }

    sprite.setTextureRect(sf::IntRect(0, 0, 21, 32));
    sprite.setPosition(horizontalPosition, verticalPosition);
    window.draw(sprite);
    horizontalPosition += 21.0f;

    if (count < 10)
    {
        sprite.setTextureRect(sf::IntRect(0, 0, 21, 32));
        sprite.setPosition(horizontalPosition, verticalPosition);
        window.draw(sprite);
        horizontalPosition += 21.0f;
    }
    else if (count < 20)
    {
        sprite.setTextureRect(sf::IntRect(21, 0, 21, 32));
        sprite.setPosition(horizontalPosition, verticalPosition);
        window.draw(sprite);
        horizontalPosition += 21.0f;
    }
    else if (count < 30)
    {
        sprite.setTextureRect(sf::IntRect(42, 0, 21, 32));
        sprite.setPosition(horizontalPosition, verticalPosition);
        window.draw(sprite);
        horizontalPosition += 21.0f;
    }
    else if (count < 40)
    {
        sprite.setTextureRect(sf::IntRect(63, 0, 21, 32));
        sprite.setPosition(horizontalPosition, verticalPosition);
        window.draw(sprite);
        horizontalPosition += 21.0f;
    }
    else if (count < 50)
    {
        sprite.setTextureRect(sf::IntRect(84, 0, 21, 32));
        sprite.setPosition(horizontalPosition, verticalPosition);
        window.draw(sprite);
        horizontalPosition += 21.0f;
    }
    else if (count < 60)
    {
        sprite.setTextureRect(sf::IntRect(105, 0, 21, 32));
        sprite.setPosition(horizontalPosition, verticalPosition);
        window.draw(sprite);
        horizontalPosition += 21.0f;
    }
    else if (count < 70)
    {
        sprite.setTextureRect(sf::IntRect(126, 0, 21, 32));
        sprite.setPosition(horizontalPosition, verticalPosition);
        window.draw(sprite);
        horizontalPosition += 21.0f;
    }
    else if (count < 80)
    {
        sprite.setTextureRect(sf::IntRect(147, 0, 21, 32));
        sprite.setPosition(horizontalPosition, verticalPosition);
        window.draw(sprite);
        horizontalPosition += 21.0f;
    }
    else if (count < 90)
    {
        sprite.setTextureRect(sf::IntRect(168, 0, 21, 32));
        sprite.setPosition(horizontalPosition, verticalPosition);
        window.draw(sprite);
        horizontalPosition += 21.0f;
    }
    else if (count < 100)
    {
        sprite.setTextureRect(sf::IntRect(189, 0, 21, 32));
        sprite.setPosition(horizontalPosition, verticalPosition);
        window.draw(sprite);
        horizontalPosition += 21.0f;
    }
    else
    {
        sprite.setTextureRect(sf::IntRect(189, 0, 21, 32));
        sprite.setPosition(horizontalPosition, verticalPosition);
        window.draw(sprite);
        horizontalPosition += 21.0f;
        sprite.setTextureRect(sf::IntRect(189, 0, 21, 32));
        sprite.setPosition(horizontalPosition, verticalPosition);
        window.draw(sprite);
    }
    
    if (count < 100)
    {
        count = count % 10;

        if (count == 0)
        {
            sprite.setTextureRect(sf::IntRect(0, 0, 21, 32));
            sprite.setPosition(horizontalPosition, verticalPosition);
            window.draw(sprite);
        }
        else if (count == 1)
        {
            sprite.setTextureRect(sf::IntRect(21, 0, 21, 32));
            sprite.setPosition(horizontalPosition, verticalPosition);
            window.draw(sprite);
        }
        else if (count == 2)
        {
            sprite.setTextureRect(sf::IntRect(42, 0, 21, 32));
            sprite.setPosition(horizontalPosition, verticalPosition);
            window.draw(sprite);
        }
        else if (count == 3)
        {
            sprite.setTextureRect(sf::IntRect(63, 0, 21, 32));
            sprite.setPosition(horizontalPosition, verticalPosition);
            window.draw(sprite);
        }
        else if (count == 4)
        {
            sprite.setTextureRect(sf::IntRect(84, 0, 21, 32));
            sprite.setPosition(horizontalPosition, verticalPosition);
            window.draw(sprite);
        }
        else if (count == 5)
        {
            sprite.setTextureRect(sf::IntRect(105, 0, 21, 32));
            sprite.setPosition(horizontalPosition, verticalPosition);
            window.draw(sprite);
        }
        else if (count == 6)
        {
            sprite.setTextureRect(sf::IntRect(126, 0, 21, 32));
            sprite.setPosition(horizontalPosition, verticalPosition);
            window.draw(sprite);
        }
        else if (count == 7)
        {
            sprite.setTextureRect(sf::IntRect(147, 0, 21, 32));
            sprite.setPosition(horizontalPosition, verticalPosition);
            window.draw(sprite);
        }
        else if (count == 8)
        {
            sprite.setTextureRect(sf::IntRect(168, 0, 21, 32));
            sprite.setPosition(horizontalPosition, verticalPosition);
            window.draw(sprite);
        }
        else if (count == 9)
        {
            sprite.setTextureRect(sf::IntRect(189, 0, 21, 32));
            sprite.setPosition(horizontalPosition, verticalPosition);
            window.draw(sprite);
        }
    }

    else
    {
        horizontalPosition -= 42.0f;
        sprite.setTextureRect(sf::IntRect(21, 0, 21, 32));
        sprite.setPosition(horizontalPosition, verticalPosition);
        window.draw(sprite);
        horizontalPosition += 21.0f;
        sprite.setTextureRect(sf::IntRect(0, 0, 21, 32));
        sprite.setPosition(horizontalPosition, verticalPosition);
        window.draw(sprite);
        horizontalPosition += 21.0f;
        sprite.setTextureRect(sf::IntRect(0, 0, 21, 32));
        sprite.setPosition(horizontalPosition, verticalPosition);
        window.draw(sprite);
        horizontalPosition += 21.0f;
    }
}

void Board::LeftMouseAction(const sf::Vector2i pos)
{
    if (face.getGlobalBounds().contains(sf::Vector2f((float)pos.x, (float)pos.y)))
    {
        SetBoard();
    }
    
    else if (debug.getGlobalBounds().contains(sf::Vector2f((float)pos.x, (float)pos.y)))
    {
        if (!minesShown)
        {
            ShowMines();
            minesShown = true;
        }
        else
        {
            HideMines();
            minesShown = false;
        }
    }

    else if (test_1.getGlobalBounds().contains(sf::Vector2f((float)pos.x, (float)pos.y)))
        TestBoard("boards/testboard1.brd");

    else if (test_2.getGlobalBounds().contains(sf::Vector2f((float)pos.x, (float)pos.y)))
        TestBoard("boards/testboard2.brd");

    else if (test_3.getGlobalBounds().contains(sf::Vector2f((float)pos.x, (float)pos.y)))
        TestBoard("boards/testboard3.brd");

    else if (active)
    {
        for (unsigned int i = 0; i < tiles.size(); i++)
        {
            if (tiles[i].sprite.getGlobalBounds().contains(sf::Vector2f((float)pos.x, (float)pos.y)) && !tiles[i].flag)
            {
                LeftMouseOnBoard(tiles[i]);
                WinTest();
            }
        }
    }
}

void Board::LeftMouseOnBoard(Tile& tile)
{
    if (tile.mine)
    {
        faceStatus = "face_lose";
        active = false;
        ShowMines();
    }
    else if (!tile.revealed)
    {
        tile.revealed = true;
        if (tile.flag)
        {
            tile.flag = false;
            flags--;
        }
        int count = 0;
        int mineCount = 0;
        for (unsigned int i = 0; i < tile.adjacentTiles.size(); i++)
        {
            if (tile.adjacentTiles[i]->mine || tile.adjacentTiles[i]->flag)
            { 
                count++;
                if (tile.adjacentTiles[i]->mine)
                    mineCount++;
            }    
        }
        if (count == 0)
        { 
            tile.key = "tile_revealed";
            for (unsigned int i = 0; i < tile.adjacentTiles.size(); i++)
                LeftMouseOnBoard(*tile.adjacentTiles[i]);
        }
        else if (mineCount > 0)
        {
            tile.key = "number_";
            tile.key += to_string(mineCount);
        }
        else
        {
            tile.key = "tile_revealed";
            for (unsigned int i = 0; i < tile.adjacentTiles.size(); i++)
            {
                if (!tile.adjacentTiles[i]->flag)
                    LeftMouseOnBoard(*tile.adjacentTiles[i]);
            }
        }
    }
}

void Board::RightMouseAction(const sf::Vector2i pos)
{
    if (active)
    {
        for (unsigned int i = 0; i < tiles.size(); i++)
        {
            if (tiles[i].sprite.getGlobalBounds().contains(sf::Vector2f((float)pos.x, (float)pos.y)) && !tiles[i].revealed)
            {
                if (!tiles[i].flag)
                {
                    if (!tiles[i].mine || !minesShown)
                        tiles[i].key = "flag";
                    tiles[i].flag = true;
                    flags++;
                }
                else
                {
                    if (minesShown && tiles[i].mine)
                        tiles[i].key = "mine";
                    else
                        tiles[i].key = "tile_hidden";
                    tiles[i].flag = false;
                    flags--;
                }
            }

        }
    }
}

void Board::WinTest()
{
    bool hidden = false;
    int count = 0;
    int mines = 0;
    for (unsigned int i = 0; i < tiles.size(); i++)
    {
        if (!tiles[i].revealed && !tiles[i].mine)
        {
            hidden = true;
            count++;
        }
        if (tiles[i].mine)
            mines++;
    }

    if (!hidden)
    {
        faceStatus = "face_win";
        active = false;
        for (unsigned int i = 0; i < tiles.size(); i++)
        {
            if (tiles[i].mine && !tiles[i].flag)
            {
                tiles[i].key = "flag";
                tiles[i].flag = true;
                flags++;
            }
        }
    }
}



Board::Tile::Tile(bool mine)
{
    this->mine = mine;
    revealed = false;
    flag = false;
    key = "tile_hidden";
}

sf::Texture& Board::Tile::GetTexture()
{
    return TextureHandler::GetTexture(key);
}

sf::Texture& Board::Tile::GetTexture(string key)
{
    return TextureHandler::GetTexture(key);
}