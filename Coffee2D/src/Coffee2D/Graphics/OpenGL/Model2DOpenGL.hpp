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

    uint64_t m_dataSize    = 0;
    uint64_t m_indicesSize = 0;

    PrimitiveType m_primitiveType = PrimitiveType::Triangles;

public:
    [[nodiscard]] bool load(const std::span<Vertex>&   data,
                            const std::span<uint64_t>& indices = {},
                            PrimitiveType type = PrimitiveType::Triangles) override;

    void unload() override;

    void render(const glm::mat4& modelMatrix, const Texture* texture, const Shader* shader) override;
};
} // namespace coffee