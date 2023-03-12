#pragma once

#include <Coffee2D/Export.hpp>
#include <string>
#include <SFML/Graphics/Transform.hpp>

namespace coffee
{
class COFFEE2D_API Shader
{
public:
    enum class ShaderType
    {
        None     = -1,
        Vertex   = 0,
        Fragment = 1
    };

    virtual ~Shader();

    [[nodiscard]] virtual bool load(ShaderType type, const std::string& source) = 0;

    virtual void destroy();

    [[nodiscard]] virtual bool compile() = 0;

    virtual std::string getShaderLog(ShaderType type) const = 0;
    virtual std::string getProgramLog() const = 0;

    virtual void useMvpMatrix(const sf::Transform& transform) const = 0;
    virtual void useTextureSlot(int textureSlot) const = 0;

    virtual void bind() const = 0;
};
}; // namespace coffee