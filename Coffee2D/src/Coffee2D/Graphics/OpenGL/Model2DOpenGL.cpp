#include "Model2DOpenGL.hpp"
#include <glad/glad.h>

namespace coffee
{
bool coffee::Model2DOpenGL::load(const std::span<Vertex>& data,
                                 const std::span<uint64_t>& indices,
                                 PrimitiveType type)
{
    // Always generate the VAO and bind it
    // Otherwise we may mess up the previously bound VAO (if any)
    if (!m_vaoid)
        glGenVertexArrays(1, &m_vaoid);

    auto vertices = indices.empty() ? data.size() : indices.size();

    switch (type)
    {
    case PrimitiveType::Triangles:
        if (vertices % 3 != 0)
            return false;
        break;
    case PrimitiveType::TriangleFan:
    case PrimitiveType::TriangleStrip:
    case PrimitiveType::LineStrip:
    case PrimitiveType::LineLoop:
        if (vertices < 3)
            return false;
        break;
    case PrimitiveType::Lines:
        if (vertices < 2)
            return false;
        break;
    default:
        return false;
    }

    glBindVertexArray(m_vaoid);

    if (!m_vboid)
        glCreateBuffers(1, &m_vboid);

    glBindBuffer(GL_ARRAY_BUFFER, m_vboid);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * data.size(), data.data(),
                 GL_STATIC_DRAW);

    // Use element draw
    if (indices.size() != 0)
    {
        if (!m_eboid)
        {
            glCreateBuffers(1, &m_eboid);
        }

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboid);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size(), indices.data(),
                     GL_STATIC_DRAW);
    }

    // Clear the element buffer if present
    else if (m_eboid)
        glDeleteBuffers(1, &m_eboid);

    glBindBuffer(GL_ARRAY_BUFFER, m_vboid);

    if (m_eboid)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboid);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, sizeof(Vertex::position) / sizeof(float), GL_FLOAT,
                          GL_FALSE, sizeof(Vertex), (void*)0);
    glVertexAttribPointer(1, sizeof(Vertex::texCoords) / sizeof(float),
                          GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)(sizeof(Vertex::position)));
    glVertexAttribPointer(
        2, sizeof(Vertex::color) / sizeof(float), GL_FLOAT, GL_FALSE,
        sizeof(Vertex),
        (void*)(sizeof(Vertex::position) + sizeof(Vertex::texCoords)));

    m_primitiveType = type;

    return true;
}

void coffee::Model2DOpenGL::unload()
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
}
} // namespace coffee