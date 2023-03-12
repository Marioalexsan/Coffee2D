#pragma once
#include <Coffee2D/Export.hpp>
#include <Coffee2D/Graphics/Shader.hpp>
#include <Coffee2D/Graphics/Texture.hpp>

#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Vertex.hpp>

#include <span>

namespace coffee
{
class COFFEE2D_API Model2D
{
public:
    enum class PrimitiveType
    {
        Triangles,
        Lines
    };

    [[nodiscard]] virtual bool update(const std::span<sf::Vertex>& data,
                                      const std::uint64_t          offset = 0) = 0;

    [[nodiscard]] virtual bool create(std::uint64_t              size,
                                      const std::span<uint32_t>& indices = {},
                                      PrimitiveType type = PrimitiveType::Triangles) = 0;

    virtual void unload() = 0;

    virtual void render(const sf::Transform& transform,
                        const Texture*       texture,
                        const Shader*        shader,
                        std::uint32_t        offset = 0,
                        std::uint32_t count = std::numeric_limits<std::uint32_t>::max()) = 0;

    Model2D()          = default;
    virtual ~Model2D() = default;
};
} // namespace coffee