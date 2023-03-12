#include "Model2DOpenGL.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace coffee
{
	bool coffee::Model2DOpenGL::load(const std::span<Vertex>& data,
		const std::span<uint64_t>& indices,
		PrimitiveType              type)
	{
		// Always generate the VAO and bind it
		// Otherwise we may mess up the previously bound VAO (if any)
		if (!m_vaoid)
			glGenVertexArrays(1, &m_vaoid);

		auto vertices = indices.size() == 0 ? data.size() : indices.size();

		switch (type)
		{
		case PrimitiveType::Triangles:
			if (vertices % 3 != 0)
				return false;
			break;
		case PrimitiveType::Lines:
			if (vertices % 2 != 0)
				return false;
			break;
		default:
			return false;
		}

		glBindVertexArray(m_vaoid);

		if (!m_vboid)
			glCreateBuffers(1, &m_vboid);

		glBindBuffer(GL_ARRAY_BUFFER, m_vboid);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * data.size(), data.data(), GL_STATIC_DRAW);
        m_dataSize = vertices;

		// Use element draw
		if (indices.size() != 0)
		{
			if (!m_eboid)
			{
				glCreateBuffers(1, &m_eboid);
			}

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboid);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size(), indices.data(), GL_STATIC_DRAW);
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
			sizeof(Vertex::position) / sizeof(Vertex::position.x),
			GL_FLOAT,
			GL_FALSE,
			sizeof(Vertex),
			(void*)0);
		glVertexAttribPointer(1,
			sizeof(Vertex::texCoords) / sizeof(Vertex::texCoords.x),
			GL_FLOAT,
			GL_FALSE,
			sizeof(Vertex),
			(void*)(sizeof(Vertex::position)));
		glVertexAttribPointer(2,
			sizeof(Vertex::color) / sizeof(Vertex::color.r),
			GL_UNSIGNED_BYTE,
			GL_FALSE,
			sizeof(Vertex),
			(void*)(sizeof(Vertex::position) + sizeof(Vertex::texCoords)));

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
	}

	void Model2DOpenGL::render(const glm::mat4& modelMatrix, const Texture* texture, const Shader* shader)
	{
		(void)modelMatrix;

		if (!m_vaoid)
			return;

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

			shader->useMvpMatrix(modelMatrix);
            shader->useTextureSlot(0);
		}

		// Draw with elements
		if (m_eboid)
		{
			if (m_primitiveType == PrimitiveType::Triangles)
			{
				glDrawElements(GL_TRIANGLES,
					static_cast<GLsizei>(m_indicesSize) / 3,
					GL_UNSIGNED_INT,
					(void*)0);
			}
			else // PrimitiveType::Lines
			{
				glDrawElements(GL_LINES,
					static_cast<GLsizei>(m_indicesSize) / 2,
					GL_UNSIGNED_INT,
					(void*)0);
			}
		}

		// Regular draw
		else
		{
			if (m_primitiveType == PrimitiveType::Triangles)
			{
                glDrawArrays(GL_TRIANGLES,
					0,
					static_cast<GLsizei>(m_dataSize));
			}
			else // PrimitiveType::Lines
			{
                glDrawArrays(GL_LINES,
					0,
					static_cast<GLsizei>(m_dataSize));
			}
		}
	}
} // namespace coffee