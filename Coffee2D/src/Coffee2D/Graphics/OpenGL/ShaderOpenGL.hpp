#pragma once
#include <Coffee2D/Graphics/Shader.hpp>

#include <glad/glad.h>

#include <array>

namespace coffee
{
class ShaderOpenGL : public Shader
{
private:
    std::array<GLuint, 2> m_shaders = {0};

    bool   m_ready   = false;
    GLuint m_program = 0;

public:
    [[nodiscard]] bool load(ShaderType type, const std::string& source) override;

    void destroy() override;

    [[nodiscard]] bool compile() override;

    std::string getShaderLog(ShaderType type) const override;
    std::string getProgramLog() const override;

    void useMvpMatrix(const glm::mat4& matrix) const override;
    void useTextureSlot(int textureSlot) const override;

    void bind() const override;
};
} // namespace coffee