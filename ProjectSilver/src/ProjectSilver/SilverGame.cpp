#include <ProjectSilver/SilverGame.hpp>
#include <iostream>

namespace silver
{
    void SilverGame::initialize()
    {
    }

    void SilverGame::update(sf::Time deltaTime)
    {
        std::clog << "Ligma balls " << deltaTime.asMicroseconds() / 1000.f
                  << std::endl;
    }

    void SilverGame::cleanup()
    {
    }

} // namespace silver