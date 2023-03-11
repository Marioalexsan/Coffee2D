#include <Coffee2D/Graphics/Vertex.hpp>

#include <ProjectSilver/SilverGame.hpp>
#include <array>
#include <iostream>

namespace silver
{
void SilverGame::initialize()
{
    m_model = getRenderer().createModel2D();

    std::array vertices =
        {coffee::Vertex({0, 0}, {0, 0}, sf::Color::White),
         coffee::Vertex({0, 100}, {0, 0}, sf::Color::White),
         coffee::Vertex({100, 100}, {0, 0}, sf::Color::White)};

    if (!m_model->load(vertices))
        throw std::runtime_error("Failed to load model.");
}

void SilverGame::update(sf::Time deltaTime)
{
    getRenderer().clear(sf::Color::Black);
    std::clog << "Ligma balls " << deltaTime.asMicroseconds() / 1000.f << std::endl;
    m_model->render({}, nullptr);
    getWindow().display();
}

void SilverGame::cleanup()
{
}

} // namespace silver