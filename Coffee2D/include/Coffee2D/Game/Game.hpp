#pragma once
#include <Coffee2D/Export.hpp>
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
    std::mutex m_mutex = {};
    bool m_running     = false;
    int m_fps          = 60;

    std::unique_ptr<sf::Window> m_window = std::make_unique<sf::Window>();

public:
    virtual ~Game();

    virtual void initialize() = 0;

    virtual void update(sf::Time deltaTime) = 0;

    virtual void cleanup() = 0;

    void run();

    void stop();

    void setFPS(int fps);
    int getFPS();

    void setViewMode(uint64_t width, uint64_t height, bool fullscreen);

private:
    void threadLoop();
};
} // namespace coffee