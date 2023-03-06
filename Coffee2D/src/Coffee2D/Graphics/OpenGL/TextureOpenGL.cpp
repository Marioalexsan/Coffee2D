#include "TextureOpenGL.hpp"

namespace coffee
{
TextureOpenGL::~TextureOpenGL()
{
}

void TextureOpenGL::load(const std::span<char>&, uint64_t, uint64_t,
                         PixelFormat)
{
    throw "Unimplemented";
}

void TextureOpenGL::unload()
{
    throw "Unimplemented";
}

} // namespace coffee