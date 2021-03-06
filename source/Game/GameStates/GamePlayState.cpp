#include <Game/GameStates/GamePlayState.hpp>

#include <SFML/Graphics.hpp>

namespace game
{
namespace gamestates
{

GamePlayState::GamePlayState(
    sf::RenderWindow& window,
    sf::Font font)
    : gamePlay_(font)
    , window_(window)
    , font_(font)
{
    music_.openFromFile("resources/gameplay.ogg");
    music_.setLoop(true);
    resume();
}

GamePlayState::~GamePlayState()
{
    pause();
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
                // TODO: use sf::View?
                window_.setSize(sf::Vector2u(event.size.width, event.size.height));
                break;
            case sf::Event::KeyReleased:
                resultState = handleKeyReleased(event);
                break;
            case sf::Event::MouseButtonPressed:
                handleMouseButtonPressed(event);
                break;
            default:
                // No need to handle other events
                break;
        }
    }

    return resultState;
}

void GamePlayState::update(const float deltaTimeSec)
{
    gamePlay_.update(deltaTimeSec);
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

void GamePlayState::resume()
{
    music_.play();
}

void GamePlayState::pause()
{
    music_.pause();
}

DesiredState GamePlayState::handleKeyReleased(const sf::Event event)
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

void GamePlayState::handleMouseButtonPressed(const sf::Event event)
{
    sf::Vector2f pos = window_.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

    switch (event.mouseButton.button)
    {
        case sf::Mouse::Left:
            gamePlay_.requestTower(sf::Vector2i(pos.x, pos.y));
            break;
        default:
            break;
    }
}

}  // namespace gamestates
}  // namespace game