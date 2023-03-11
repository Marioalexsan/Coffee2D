#pragma once

#include <string>

namespace coffee
{
class Shader
{
public:
    enum class ShaderType
    {
        None     = -1,
        Vertex   = 0,
        Fragment = 1
    };

    virtual ~Shader() = default;

    [[nodicard]] virtual bool load(ShaderType type, const std::string& source) = 0;

    [[nodicard]] virtual bool unload() = 0;

    virtual const std::string& getShaderLog(ShaderType type) const;
    virtual const std::string& getProgramLog() const;
};
}; // namespace coffee