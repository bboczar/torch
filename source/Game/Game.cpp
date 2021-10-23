#include <Game/Game.hpp>

#include <SFML/Window.hpp>

namespace game
{

int Game::start()
{
    sf::Window window(sf::VideoMode(800, 600), "Torch");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    return 0;
}

}  // namespace game