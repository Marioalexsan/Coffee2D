#pragma once
#include <Coffee2D/Graphics/Texture.hpp>

namespace coffee
{
class COFFEE2D_API TextureOpenGL : public Texture
{
public:
    ~TextureOpenGL();

    void load(const std::span<char>& data, uint64_t width, uint64_t height, PixelFormat format) override;

    void unload() override;
};
}