#include "TextureOpenGL.hpp"
#include <unordered_map>

namespace
{
const std::unordered_map<coffee::Texture::PixelFormat, GLint> formatMap = {
    {coffee::Texture::PixelFormat::RGB, GL_RGB},
    {coffee::Texture::PixelFormat::RGBA, GL_RGBA}};

const std::unordered_map<coffee::Texture::PixelFormat, uint64_t> formatSize = {
    {coffee::Texture::PixelFormat::RGB, 24},
    {coffee::Texture::PixelFormat::RGBA, 32}};
} // namespace

namespace coffee
{
TextureOpenGL::~TextureOpenGL()
{
    unload();
}

bool TextureOpenGL::load(const std::span<char>& data, uint64_t width,
                         uint64_t height, PixelFormat format)
{
    if (!formatMap.contains(format))
        return false;

    if (width * height * (formatSize.at(format) / 8) > data.size())
        return false;

    m_width  = width;
    m_height = height;

    GLint pixelFormat = formatMap.at(format);

    if (!m_handle)
    {
        glGenTextures(1, &m_handle);
    }

    glBindTexture(GL_TEXTURE_2D, m_handle);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)width, (GLsizei)height, 0, pixelFormat,
                 GL_UNSIGNED_BYTE, data.data());
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return true;
}

void TextureOpenGL::unload()
{
    if (m_handle)
    {
        glDeleteTextures(1, &m_handle);
        m_handle = 0;
    }
}

void TextureOpenGL::bind() const
{
    if (m_handle)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_handle);
    }
}

sf::Vector2u TextureOpenGL::getSize() const
{
    return {(unsigned int)m_width, (unsigned int)m_height};
}

} // namespace coffee