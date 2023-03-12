#pragma once
#include <Coffee2D/Export.hpp>
#include <Coffee2D/Graphics/Model2D.hpp>

#include <glad/glad.h>

#include <span>

namespace coffee
{
class COFFEE2D_API Model2DOpenGL : public Model2D
{
private:
    GLuint m_vaoid = 0;
    GLuint m_vboid = 0;
    GLuint m_eboid = 0;

    uint64_t m_dataSize       = 0;
    uint64_t m_indicesSize    = 0;
    uint64_t m_primitiveCount = 0;

    PrimitiveType m_primitiveType = PrimitiveType::Triangles;

public:
    [[nodiscard]] bool update(const std::span<sf::Vertex>& data,
                              const std::uint64_t          offset = 0) override;

    [[nodiscard]] bool create(std::uint64_t              size,
                              const std::span<uint32_t>& indices = {},
                              PrimitiveType type = PrimitiveType::Triangles) override;

    void unload() override;

    void render(const sf::Transform& transform,
                const Texture*       texture,
                const Shader*        shader,
                std::uint32_t        offset = 0,
                std::uint32_t count = std::numeric_limits<std::uint32_t>::max()) override;
};
} // namespace coffee