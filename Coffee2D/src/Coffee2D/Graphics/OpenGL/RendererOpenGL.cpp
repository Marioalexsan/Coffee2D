#include "RendererOpenGL.hpp"
#include "TextureOpenGL.hpp"
#include "Model2DOpenGL.hpp"
#include <glad/glad.h>

namespace coffee
{
RendererOpenGL::RendererOpenGL()
{
    gladLoadGL();

    if (!GLAD_GL_VERSION_4_6)
        throw std::runtime_error("Failed to load OpenGL 4.6");
}

RendererOpenGL::~RendererOpenGL()
{
}

void RendererOpenGL::clear(sf::Color color)
{
    glClearColor(color.r / 255.f, color.g / 255.f, color.b / 255.f,
                 color.a / 255.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RendererOpenGL::setView()
{
}

std::unique_ptr<Texture> RendererOpenGL::createTexture()
{
    return std::make_unique<TextureOpenGL>();
}

std::unique_ptr<Model2D> RendererOpenGL::createModel2D()
{
    return std::make_unique<Model2DOpenGL>();
}

} // namespace coffee