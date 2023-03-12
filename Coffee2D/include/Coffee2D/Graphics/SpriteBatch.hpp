#pragma once

#include <Coffee2D/Export.hpp>
#include <Coffee2D/Graphics/Renderer.hpp>

namespace coffee
{
class COFFEE2D_API SpriteBatch
{
private:
    static const std::size_t PreferredBatchSize = 1024; // in sprites

    std::unique_ptr<Model2D> m_model;
    std::uint64_t            m_modelSize = 0;
    Renderer*                m_renderer  = 0;

    const Shader*           m_batchShader  = nullptr;
    const Texture*          m_batchTexture = nullptr;
    std::vector<sf::Vertex> m_vertices;

    sf::View m_view;

public:
    SpriteBatch(Renderer& renderer);

    void            setView(const sf::View& view);
    const sf::View& getView();

    void drawSprite(const Texture& texture,
                    sf::Vector2f   position,
                    sf::Angle      rotation,
                    sf::Vector2f   scale,
                    sf::Vector2f   center,
                    sf::Color      color,
                    const Shader*  shader);

    void flush();
};
} // namespace coffee