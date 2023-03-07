#pragma once
#include <Coffee2D/Export.hpp>
#include <SFML/Graphics/Color.hpp>
#include <glm/glm.hpp>

namespace coffee
{
struct COFFEE2D_API Vertex
{
    Vertex() = default;
    Vertex(glm::vec2 position, glm::vec2 texCoords, sf::Color color);

    glm::vec2 position;
    glm::vec2 texCoords;
    sf::Color color;
};
} // namespace coffee