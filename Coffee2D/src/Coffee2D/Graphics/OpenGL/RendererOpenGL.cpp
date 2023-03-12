#include "RendererOpenGL.hpp"

#include <glad/glad.h>

#include "Model2DOpenGL.hpp"
#include "ShaderOpenGL.hpp"
#include "TextureOpenGL.hpp"

namespace coffee
{
RendererOpenGL::RendererOpenGL()
{
    gladLoadGL();

    if (!GLAD_GL_VERSION_4_6)
        throw std::runtime_error("Failed to load OpenGL 4.6");

    glDisable(GL_CULL_FACE);
}

RendererOpenGL::~RendererOpenGL()
{
}

void RendererOpenGL::clear(sf::Color color)
{
    glClearColor(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

std::unique_ptr<Texture> RendererOpenGL::createTexture()
{
    return std::make_unique<TextureOpenGL>();
}

std::unique_ptr<Model2D> RendererOpenGL::createModel2D()
{
    return std::make_unique<Model2DOpenGL>();
}

std::unique_ptr<Shader> RendererOpenGL::createShader()
{
    return std::make_unique<ShaderOpenGL>();
}

} // namespace coffee