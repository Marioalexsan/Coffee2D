#pragma once
#include <Coffee2D/Export.hpp>
#include <Coffee2D/Graphics/Model2D.hpp>
#include <Coffee2D/Graphics/Renderer.hpp>
#include <Coffee2D/Graphics/SpriteBatch.hpp>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <chrono>
#include <memory>
#include <mutex>
#include <thread>

namespace coffee
{
class COFFEE2D_API Game
{
private:
    std::mutex m_mutex   = {};
    bool       m_running = false;
    int        m_fps     = 60;

    std::unique_ptr<sf::Window>  m_window;
    std::unique_ptr<Renderer>    m_renderer;
    std::unique_ptr<SpriteBatch> m_spriteBatch;

public:
    Game();
    virtual ~Game();

    virtual void initialize() = 0;

    virtual void update(sf::Time deltaTime) = 0;

    virtual void cleanup() = 0;

    void run();

    void stop();

    void setFPS(int fps);
    int  getFPS();

    void setViewMode(uint64_t width, uint64_t height, bool fullscreen);

    Renderer&    getRenderer();
    sf::Window&  getWindow();
    SpriteBatch& getSpriteBatch();

private:
    void threadLoop();
    void processEvents();
};
} // namespace coffee