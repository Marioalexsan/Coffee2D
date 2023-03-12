#include <Coffee2D/Graphics/Shader.hpp>

namespace coffee
{
Shader::~Shader()
{
    destroy();
}

void Shader::destroy()
{
    // Empty implementation for use in destructor
}
}