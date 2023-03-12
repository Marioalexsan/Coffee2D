#include "ShaderOpenGL.hpp"

#include <glad/glad.h>

#include <unordered_map>

namespace
{
const std::unordered_map<coffee::Shader::ShaderType, GLenum> shaderTypeMap =
    {{coffee::Shader::ShaderType::Vertex, GL_VERTEX_SHADER},
     {coffee::Shader::ShaderType::Fragment, GL_FRAGMENT_SHADER}};

const std::unordered_map<coffee::Shader::ShaderType, std::string> shaderDisplay =
    {{coffee::Shader::ShaderType::Vertex, "Vertex Shader"},
     {coffee::Shader::ShaderType::Fragment, "Fragment Shader"}};
} // namespace

namespace coffee
{
bool ShaderOpenGL::load(ShaderType type, const std::string& source)
{
    if (!shaderTypeMap.contains(type))
        return false;

    m_ready = false;

    GLuint& shader = m_shaders[static_cast<std::size_t>(type)];

    if (!shader)
        shader = glCreateShader(shaderTypeMap.at(type));

    const char* data   = source.c_str();
    GLint       length = static_cast<GLint>(source.size());

    glShaderSource(shader, 1, &data, &length);
    glCompileShader(shader);

    GLint status = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    return status == GL_TRUE;
}

void ShaderOpenGL::destroy()
{
    m_ready = false;

    for (auto& shader : m_shaders)
    {
        if (shader)
        {
            if (m_program)
                glDetachShader(m_program, shader);

            glDeleteShader(shader);
        }
    }

    if (m_program)
        glDeleteProgram(m_program);
}

bool ShaderOpenGL::compile()
{
    if (m_ready)
        return true;

    if (!m_program)
        m_program = glCreateProgram();

    for (auto& shader : m_shaders)
    {
        if (shader)
        {
            glAttachShader(m_program, shader);
        }
    }

    glLinkProgram(m_program);

    GLint status = GL_FALSE;
    glGetProgramiv(m_program, GL_LINK_STATUS, &status);

    return m_ready = (status == GL_TRUE);
}

std::string ShaderOpenGL::getShaderLog(Shader::ShaderType type) const
{
    std::size_t index = static_cast<std::size_t>(type);

    if (!shaderTypeMap.contains(type) || !m_shaders[index])
        return "Not created.";

    int length = 0, written = 0;

    std::string log;

    glGetShaderiv(m_shaders[index], GL_INFO_LOG_LENGTH, &length);

    std::string data = std::string(length, ' ');

    if (length > 0)
        glGetShaderInfoLog(m_shaders[index], length, &written, data.data());

    return data;
}

std::string ShaderOpenGL::getProgramLog() const
{
    if (!m_program)
        return "Not created.";

    int length = 0, written = 0;

    std::string log;

    glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &length);

    if (length > 0)
    {
        std::string data = std::string(length, ' ');

        glGetProgramInfoLog(m_program, length, &written, data.data());

        log += "Program error log: \n" + data;
    }

    return log;
}

void ShaderOpenGL::bind() const
{
    if (m_program)
        glUseProgram(m_program);
}

void ShaderOpenGL::useMvpMatrix(const sf::Transform& transform) const
{
    GLuint matrixID = glGetUniformLocation(m_program, "mvpMatrix");
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, transform.getMatrix());
}

void ShaderOpenGL::useTextureSlot(int textureSlot) const
{
    GLuint texID = glGetUniformLocation(m_program, "tex");
    glUniform1i(texID, textureSlot);
}

} // namespace coffee