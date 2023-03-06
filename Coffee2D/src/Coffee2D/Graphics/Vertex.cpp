#include <Coffee2D/Graphics/Vertex.hpp>

namespace coffee
{
Vertex::Vertex(glm::vec3 position, glm::vec2 texCoords, sf::Color color)
    : position(position)
    , texCoords(texCoords)
    , color(color)
{
}
} // namespace coffee