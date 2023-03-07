#pragma once
#include <Coffee2D/Export.hpp>
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
        TriangleFan,
        TriangleStrip,
        Lines,
        LineStrip,
        LineLoop
    };

    [[nodiscard]] virtual bool load(
        const std::span<Vertex>& data, const std::span<uint64_t>& indices = {},
        PrimitiveType type = PrimitiveType::Triangles) = 0;

    virtual void unload() = 0;

    Model2D() = default;
    virtual ~Model2D() = default;
};
} // namespace coffee