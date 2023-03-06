#pragma once
#include <Coffee2D/Export.hpp>
#include <glm/glm.hpp>
#include <SFML/Graphics/Color.hpp>

namespace coffee {
struct COFFEE2D_API Vertex
{
    Vertex() = default;
    Vertex(glm::vec3 position, glm::vec2 texCoords, sf::Color color);

    glm::vec3 position;
    glm::vec2 texCoords;
    sf::Color color;
};
} // namespace coffee