#include <Game/GameStates/GamePlayState.hpp>

#include <SFML/Graphics.hpp>

namespace game
{
namespace gamestates
{

GamePlayState::GamePlayState(
    sf::RenderWindow& window,
    sf::Font font)
    : window_(window)
    , font_(font)
{
}

std::optional<GameStateType> GamePlayState::handleEvents()
{
    std::optional<GameStateType> resultState = GameStateType::GamePlay;
    sf::Event event;

    while (window_.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window_.close();
                break;
            case sf::Event::Resized:
                // TODO: fix
                window_.setSize(sf::Vector2u(event.size.width, event.size.height));
                break;
            case sf::Event::KeyReleased:
                resultState = handleKeyPressed(event);
            default:
                // No need to handle other events
                break;
        }
    }

    return resultState;
}

void GamePlayState::update()
{
    gamePlay_.update();
}

void GamePlayState::draw()
{
    window_.clear(sf::Color::Black);
    gamePlay_.draw(window_);
}

GameStateType GamePlayState::type() const
{
    return GameStateType::GamePlay;
}

DesiredState GamePlayState::handleKeyPressed(const sf::Event event)
{
    DesiredState state = GameStateType::GamePlay;

    switch (event.key.code)
    {
        case sf::Keyboard::Escape:
            return std::nullopt;
        default:
            break;
    }

    return state;
}

}  // namespace gamestates
}  // namespace game