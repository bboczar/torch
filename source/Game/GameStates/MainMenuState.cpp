#include <Game/GameStates/MainMenuState.hpp>

#include <SFML/Graphics.hpp>

namespace game
{
namespace gamestates
{

MainMenuState::MainMenuState(
    sf::RenderWindow& window,
    sf::Font font)
    : window_(window)
    , menu_(mainmenu::MainMenu(font))
{
}

std::optional<GameStateType> MainMenuState::handleEvents()
{
    std::optional<GameStateType> resultState = GameStateType::MainMenu;
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

void MainMenuState::update(const float)
{
    return;
}

void MainMenuState::draw()
{
    window_.clear(sf::Color::Black);
    menu_.draw(window_);
}

GameStateType MainMenuState::type() const
{
    return GameStateType::MainMenu;
}

DesiredState MainMenuState::handleKeyPressed(const sf::Event event)
{
    DesiredState state = GameStateType::MainMenu;

    switch (event.key.code)
    {
        case sf::Keyboard::Up:
            menu_.moveUp();
            break;
        case sf::Keyboard::Down:
            menu_.moveDown();
            break;
        case sf::Keyboard::Enter:
            state = resolveState(menu_.selectEntry());
            break;
        case sf::Keyboard::Escape:
            window_.close();
            break;
        default:
            break;
    }

    return state;
}

DesiredState MainMenuState::resolveState(mainmenu::MainMenu::MenuElement entry)
{
    switch (entry)
    {
        case mainmenu::MainMenu::MenuElement_Start:
            return GameStateType::GamePlay;
        case mainmenu::MainMenu::MenuElement_Options:
            return GameStateType::Options;
        case mainmenu::MainMenu::MenuElement_Exit:
            return std::nullopt;
        default:
            return std::nullopt;
    }
}

}  // namespace gamestates
}  // namespace game