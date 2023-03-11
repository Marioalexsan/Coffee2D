#pragma once
#include <Coffee2D/Export.hpp>
#include <Coffee2D/Graphics/Renderer.hpp>

namespace coffee
{
class COFFEE2D_API RendererOpenGL : public Renderer
{
public:
    RendererOpenGL();
    ~RendererOpenGL();

    void clear(sf::Color color) override;

    std::unique_ptr<Texture> createTexture() override;
    std::unique_ptr<Model2D> createModel2D() override;

    void setView() override;
};
} // namespace coffee