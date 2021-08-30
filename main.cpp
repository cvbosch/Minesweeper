#include "Board.h"
#include "TextureHandler.h"
#include "Board.h"
#include <iostream>
using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper");
    window.setVerticalSyncEnabled(true);
    Board board = Board(25, 16, 50);
    
    TextureHandler::AllTextures();
    
     sf::Sprite bottomSprite(TextureHandler::GetTexture("tile_revealed"));
     sf::Sprite sprite;


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    board.LeftMouseAction(sf::Mouse::getPosition(window));
                }
                else if (event.mouseButton.button == sf::Mouse::Right)
                {
                    board.RightMouseAction(sf::Mouse::getPosition(window));
                }
            }
        }

        window.clear(sf::Color(255, 255, 255));

        board.DrawBase(window, bottomSprite);
        board.Draw(window, sprite);

        window.display();
    }

    TextureHandler::Clear();

    return 0;
}