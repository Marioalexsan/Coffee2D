#pragma once
#include <glad/glad.h>

#include <Coffee2D/Graphics/Texture.hpp>

namespace coffee
{
class COFFEE2D_API TextureOpenGL : public Texture
{
private:
    GLuint   m_handle = 0;
    uint64_t m_width  = 0;
    uint64_t m_height = 0;

public:
    ~TextureOpenGL();

    [[nodiscard]] bool load(const std::span<char>& data,
                            uint64_t               width,
                            uint64_t               height,
                            PixelFormat            format) override;

    sf::Vector2u getSize() const override;

    void unload() override;

    void bind() const override;
};
} // namespace coffee