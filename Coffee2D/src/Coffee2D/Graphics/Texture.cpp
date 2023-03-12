#include <Coffee2D/Graphics/Texture.hpp>

#include <stb/stb_image.h>

namespace coffee
{
Texture::~Texture()
{
}

bool Texture::loadFromFile(const std::filesystem::path& path)
{
    int width = 0, height = 0, nrChannels = 0;

    std::unique_ptr<uint8_t, void (*)(uint8_t*)>
        data(stbi_load(path.string().c_str(), &width, &height, &nrChannels, 0),
             [](uint8_t* ptr) { stbi_image_free(ptr); });

    if (nrChannels == 3)
        return load(std::span(data.get(), width * height * 3), width, height, PixelFormat::RGB);

    else if (nrChannels == 4)
        return load(std::span(data.get(), width * height * 4), width, height, PixelFormat::RGBA);

    else
        return false;
}
} // namespace coffee