#pragma once
#include <Coffee2D/Export.hpp>
#include <filesystem>
#include <span>

namespace coffee
{
class COFFEE2D_API Texture
{
public:
    enum class PixelFormat
    {
        RGB,
        RGBA
    };

    virtual ~Texture();

    virtual void load(const std::span<char>& data, uint64_t width, uint64_t height, PixelFormat format) = 0;

    virtual void unload() = 0;

    void loadFromFile(const std::filesystem::path& path);
};
} // namespace coffee