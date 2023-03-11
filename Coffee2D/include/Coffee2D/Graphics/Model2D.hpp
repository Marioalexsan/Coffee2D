#pragma once
#include <Coffee2D/Export.hpp>
#include <Coffee2D/Graphics/Texture.hpp>
#include <Coffee2D/Graphics/Vertex.hpp>
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

    [[nodiscard]] virtual bool load(const std::span<Vertex>&   data,
                                    const std::span<uint64_t>& indices = {},
                                    PrimitiveType type = PrimitiveType::Triangles) = 0;

    virtual void unload() = 0;

    virtual void render(const glm::mat4& mvpMatrix, const Texture* texture) = 0;

    Model2D()          = default;
    virtual ~Model2D() = default;
};
} // namespace coffee