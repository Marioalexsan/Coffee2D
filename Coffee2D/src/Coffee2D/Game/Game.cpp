#include <Coffee2D/Game/Game.hpp>

#include <SFML/Window.hpp>

#include <atomic>

#include "../Graphics/OpenGL/RendererOpenGL.hpp"

namespace coffee
{
Game::Game()
{
    m_window = std::make_unique<sf::Window>(sf::VideoMode({1280, 720}),
                                            "Hello world!",
                                            sf::Style::Titlebar | sf::Style::Close,
                                            sf::ContextSettings(24, 8, 0, 4, 6));

    m_renderer    = std::make_unique<RendererOpenGL>();
    m_spriteBatch = std::make_unique<SpriteBatch>(*m_renderer);
}

Game::~Game()
{
}

void Game::run()
{
    // Have we started already?
    if (m_running)
        return;

    m_running = true;
    threadLoop();
}

void Game::stop()
{
    // Have we stopped already?
    if (!m_running)
        return;

    m_running = false;
}

void Game::setFPS(int fps)
{
    // Limit FPS to sane values
    m_fps = std::clamp(fps, 1, 10000);
}

void Game::setViewMode(uint64_t width, uint64_t height, bool fullscreen)
{
    if (m_window)
    {
        auto contextSettings = sf::ContextSettings(24, 8, 0, 4, 6, sf::ContextSettings::Attribute::Core);

        uint32_t styles = sf::Style::None;

        if (fullscreen)
            styles |= sf::Style::Fullscreen;
        else
            styles |= sf::Style::Titlebar;

        m_window->create(sf::VideoMode{{(unsigned int)width, (unsigned int)height}},
                         "Game",
                         styles,
                         contextSettings);
    }
}

Renderer& Game::getRenderer()
{
    return *m_renderer;
}

sf::Window& Game::getWindow()
{
    return *m_window;
}

void Game::threadLoop()
{
    initialize();

    sf::Clock timer;
    sf::Time  accumulator;
    sf::Time  worstSleepTime = sf::milliseconds(4);

    while (m_running)
    {
        processEvents();

        // Calculate target time to sleep
        sf::Time frameTime = sf::seconds(1) / (float)m_fps;

        accumulator += timer.restart();

        while (accumulator + worstSleepTime < frameTime)
        {
            sf::sleep(sf::milliseconds(1));

            accumulator += timer.restart();
        }

        while (accumulator < frameTime)
        {
            // TODO Implement spinwait
            sf::sleep(sf::milliseconds(1));

            accumulator += timer.restart();
        }

        while (accumulator > frameTime)
        {
            update(frameTime);
            accumulator -= frameTime;
        }
    }

    cleanup();
}

SpriteBatch& Game::getSpriteBatch()
{
    return *m_spriteBatch;
}

void Game::processEvents()
{
    sf::Event event;
    while (m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_running = false;
    }
}

} // namespace coffee