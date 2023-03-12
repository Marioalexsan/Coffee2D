#include "Model2DOpenGL.hpp"

namespace coffee
{
bool Model2DOpenGL::update(const std::span<sf::Vertex>& data, const std::uint64_t offset)
{
    if (!m_vaoid || !m_vboid)
        return false;

    if (data.size() + offset > m_dataSize)
        return false;

    glBindVertexArray(m_vaoid);
    glBufferSubData(GL_ARRAY_BUFFER,
                    offset * sizeof(sf::Vertex),
                    data.size() * sizeof(sf::Vertex),
                    data.data());

    return true;
}

bool Model2DOpenGL::create(std::uint64_t size, const std::span<uint32_t>& indices, PrimitiveType type)
{
    // Always generate the VAO and bind it
    // Otherwise we may mess up the previously bound VAO (if any)
    if (!m_vaoid)
        glGenVertexArrays(1, &m_vaoid);

    auto indexCount = indices.size() == 0 ? size : indices.size();

    switch (type)
    {
        case PrimitiveType::Triangles:
            if (indexCount % 3 != 0)
                return false;
            m_primitiveCount = indexCount / 3;
            break;
        case PrimitiveType::Lines:
            if (indexCount % 2 != 0)
                return false;
            m_primitiveCount = indexCount / 2;
            break;
        default:
            return false;
    }

    glBindVertexArray(m_vaoid);

    if (!m_vboid)
        glCreateBuffers(1, &m_vboid);

    glBindBuffer(GL_ARRAY_BUFFER, m_vboid);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sf::Vertex) * size, nullptr, GL_STATIC_DRAW);
    m_dataSize = size;

    // Use element draw
    if (indices.size() != 0)
    {
        if (!m_eboid)
        {
            glCreateBuffers(1, &m_eboid);
        }

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboid);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     indices.size() * sizeof(indices[0]),
                     indices.data(),
                     GL_STATIC_DRAW);
        m_indicesSize = indices.size();
    }

    // Clear the element buffer if present
    else if (m_eboid)
    {
        glDeleteBuffers(1, &m_eboid);
        m_eboid       = 0;
        m_indicesSize = 0;
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_vboid);

    if (m_eboid)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboid);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0,
                          sizeof(sf::Vertex::position) / sizeof(sf::Vertex::position.x),
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(sf::Vertex),
                          (void*)(offsetof(sf::Vertex, position)));
    glVertexAttribPointer(1,
                          sizeof(sf::Vertex::color) / sizeof(sf::Vertex::color.r),
                          GL_UNSIGNED_BYTE,
                          GL_TRUE,  // Color needs to be normalized from [0, 255] to [0, 1]
                          sizeof(sf::Vertex),
                          (void*)(offsetof(sf::Vertex, color)));
    glVertexAttribPointer(2,
                          sizeof(sf::Vertex::texCoords) / sizeof(sf::Vertex::texCoords.x),
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(sf::Vertex),
                          (void*)(offsetof(sf::Vertex, texCoords)));

    m_primitiveType = type;

    return true;
}

void Model2DOpenGL::unload()
{
    if (m_vaoid)
    {
        glDeleteVertexArrays(1, &m_vaoid);
        m_vaoid = 0;
    }

    if (m_vboid)
    {
        glDeleteBuffers(1, &m_vboid);
        m_vboid = 0;
    }

    if (m_eboid)
    {
        glDeleteBuffers(1, &m_eboid);
        m_eboid = 0;
    }

    m_primitiveCount = 0;
    m_dataSize       = 0;
    m_indicesSize    = 0;
}

void Model2DOpenGL::render(const sf::Transform& transform,
                           const Texture*       texture,
                           const Shader*        shader,
                           std::uint32_t        offset,
                           std::uint32_t        count)
{
    if (!m_vaoid)
        return;

    if (offset < 0 || (std::uint64_t)offset > m_primitiveCount)
        return;

    if ((uint64_t)offset + count >= m_primitiveCount)
        count = (uint32_t)(m_primitiveCount - offset);

    glBindVertexArray(m_vaoid);

    if (texture)
        texture->bind();

    else
    {
        // TODO Fix null textures
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    if (shader)
    {
        shader->bind();

        shader->useMvpMatrix(transform);
        shader->useTextureSlot(0);
    }

    // Draw with elements
    if (m_eboid)
    { 
        if (m_primitiveType == PrimitiveType::Triangles)
        {
            glDrawElements(GL_TRIANGLES,
                           count * 3,
                           GL_UNSIGNED_INT,
                           reinterpret_cast<void*>((uint64_t)offset * 3));
        }
        else // PrimitiveType::Lines
        {
            glDrawElements(GL_LINES,
                           count * 2,
                           GL_UNSIGNED_INT,
                           reinterpret_cast<void*>((uint64_t)offset * 2));
        }
    }

    // Regular draw
    else
    {
        if (m_primitiveType == PrimitiveType::Triangles)
        {
            glDrawArrays(GL_TRIANGLES, offset * 3, count * 3);
        }
        else // PrimitiveType::Lines
        {
            glDrawArrays(GL_LINES, offset * 2, count * 2);
        }
    }
}
} // namespace coffee