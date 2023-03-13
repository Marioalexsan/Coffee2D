#include <Coffee2D/Graphics/SpriteBatch.hpp>

#include <array>

/*

Sprite Indices:

    0---3
    |  /|
    | / |
    |/  |
    1---2

*/

namespace coffee
{
SpriteBatch::SpriteBatch(Renderer& renderer)
{
    m_renderer = &renderer;
    m_model    = renderer.createModel2D();

    // Pretile element array buffer
    // This allows us to send 4 vertices per sprite instead of 6
    std::vector<std::uint32_t> indices(PreferredBatchSize * 6);
    std::size_t                vertex = 0;

    for (std::size_t sprite = 0; sprite < PreferredBatchSize; vertex += 4)
    {
        // Assign consecutively
        indices[sprite++] = vertex + 0;
        indices[sprite++] = vertex + 1;
        indices[sprite++] = vertex + 3;
        indices[sprite++] = vertex + 1;
        indices[sprite++] = vertex + 2;
        indices[sprite++] = vertex + 3;
    }

    if (!m_model->create(PreferredBatchSize * 4, indices))
        throw std::runtime_error("Failed to create SpriteBatch model.");

    m_vertices.reserve(PreferredBatchSize * 4);
}

void SpriteBatch::drawSprite(const Texture& texture,
                             sf::Vector2f   position,
                             sf::Angle      rotation,
                             sf::Vector2f   scale,
                             sf::Vector2f   center,
                             sf::Color      color,
                             const Shader*  shader)
{
    // Do we need a new batch?

    if (m_batchTexture != &texture || m_batchShader != shader)
    {
        flush();
        m_batchShader  = shader;
        m_batchTexture = &texture;
    }

    sf::Transform transform = m_view.getTransform();

    transform.translate(position);
    transform.rotate(rotation);
    transform.scale(scale);
    transform.translate(-center);

    sf::Vector2f texSize = (sf::Vector2f)texture.getSize();

    std::array<sf::Vector2f, 4> texCoods =
        {sf::Vector2f(0, texSize.y), sf::Vector2f(0, 0), sf::Vector2f(texSize.x, 0), texSize};

    std::array<sf::Vector2f, 4> positions =
        {sf::Vector2f(0, 0), sf::Vector2f(0, texSize.y), texSize, sf::Vector2f(texSize.x, 0)};

    m_vertices.emplace_back(transform * positions[0], color, texCoods[0].cwiseDiv(texSize));
    m_vertices.emplace_back(transform * positions[1], color, texCoods[1].cwiseDiv(texSize));
    m_vertices.emplace_back(transform * positions[2], color, texCoods[2].cwiseDiv(texSize));
    m_vertices.emplace_back(transform * positions[3], color, texCoods[3].cwiseDiv(texSize));

    // Do we need to flush current batch?

    if (m_vertices.size() >= PreferredBatchSize * 4)
        flush();
}

void SpriteBatch::flush()
{
    if (m_vertices.size() == 0)
        return;

    if (!m_model->update(std::span<sf::Vertex>(m_vertices.begin(), m_vertices.end())))
        return;

    m_model->render(sf::Transform::Identity,
                    m_batchTexture,
                    m_batchShader,
                    0,
                    m_vertices.size() / 2); // 2 trianges per 4 vertices

    m_vertices.clear();
}

void SpriteBatch::setView(const sf::View& view)
{
    m_view = view;
}

const sf::View& SpriteBatch::getView()
{
    return m_view;
}

} // namespace coffee