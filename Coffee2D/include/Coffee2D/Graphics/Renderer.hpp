#pragma once
#include <Coffee2D/Export.hpp>
#include <Coffee2D/Graphics/Texture.hpp>
#include <Coffee2D/Graphics/VertexBuffer.hpp>
#include <SFML/Graphics/Color.hpp>
#include <glm/glm.hpp>
#include <memory>
#include <span>

namespace coffee
{
class COFFEE2D_API Renderer
{
public:
    enum class PrimitiveType
    {
        Triangles
    };

    virtual ~Renderer();

    virtual void clear(sf::Color color) = 0;

    virtual std::unique_ptr<Texture> createTexture()           = 0;
    virtual std::unique_ptr<VertexBuffer> createVertexBuffer() = 0;

    virtual void setView() = 0;
};
} // namespace coffee