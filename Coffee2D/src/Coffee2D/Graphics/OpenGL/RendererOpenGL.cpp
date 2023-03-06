#include "RendererOpenGL.hpp"
#include <glad/glad.h>
#include "TextureOpenGL.hpp"

namespace coffee
{
RendererOpenGL::~RendererOpenGL()
{
}

void RendererOpenGL::clear(sf::Color color)
{
    glClearColor(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RendererOpenGL::setView()
{
}

std::unique_ptr<Texture> RendererOpenGL::createTexture()
{
    return std::make_unique<TextureOpenGL>();
}

std::unique_ptr<VertexBuffer> RendererOpenGL::createVertexBuffer()
{
    throw "Unimplemented";
}

} // namespace coffee