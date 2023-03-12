#pragma once
#include <Coffee2D/Export.hpp>
#include <Coffee2D/Graphics/Model2D.hpp>
#include <Coffee2D/Graphics/Shader.hpp>
#include <Coffee2D/Graphics/Texture.hpp>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/View.hpp>

#include <memory>
#include <span>

namespace coffee
{
class COFFEE2D_API Renderer
{
public:
    enum class PrimitiveType
    {
        Triangles
    };

    virtual ~Renderer();

    virtual void clear(sf::Color color) = 0;

    virtual std::unique_ptr<Texture> createTexture() = 0;
    virtual std::unique_ptr<Model2D> createModel2D() = 0;
    virtual std::unique_ptr<Shader>  createShader()  = 0;
};
} // namespace coffee