#include <Coffee2D/Graphics/Vertex.hpp>

#include <glm/gtc/type_ptr.hpp>
#include <ProjectSilver/SilverGame.hpp>
#include <array>
#include <iostream>

namespace
{
const std::string fs_code =
    "#version 400\n"

    "in vec2 Position;"
    "in vec2 TexCoord;"
    "in vec4 Color;"

    "out vec4 FragColor;"

    "uniform sampler2D tex;"

    "void main()"
    "{"
    //"FragColor = Color * texture(tex, TexCoord);"
    "FragColor = Color;"
    "}";

const std::string vs_code =
    "#version 400\n"

    "layout(location = 0) in vec2 aPos;"
    "layout(location = 1) in vec2 aTexCoord;"
    "layout(location = 2) in vec4 aColor;"

    "out vec2 Position;"
    "out vec2 TexCoord;"
    "out vec4 Color;"

    "uniform sampler2D tex;"
    "uniform mat4x4 mvpMatrix;"

    "void main()"
    "{"
    "gl_Position = mvpMatrix * vec4(aPos, 0.0, 1.0);"
    "Color = aColor;"
    "TexCoord = aTexCoord;"
    "Position = aPos;"
    "}";
} // namespace

namespace silver
{
void SilverGame::initialize()
{
    m_model = getRenderer().createModel2D();

    std::array vertices = {coffee::Vertex({0, 0}, {0, 0}, sf::Color::White),
                           coffee::Vertex({0, 100}, {0, 0}, sf::Color::White),
                           coffee::Vertex({100, 100}, {0, 0}, sf::Color::White)};

    if (!m_model->load(vertices))
    {
        std::clog << "Failed to load model." << std::endl;
        std::abort();
    }

    m_shader = getRenderer().createShader();

    using ShaderType = coffee::Shader::ShaderType;

    if (!m_shader->load(ShaderType::Vertex, vs_code))
    {
        std::clog << "Failed to load shader." << std::endl;
        std::clog << m_shader->getShaderLog(ShaderType::Vertex);
        std::abort();
    }

    if (!m_shader->load(ShaderType::Fragment, fs_code))
    {
        std::clog << "Failed to load shader." << std::endl;
        std::clog << m_shader->getShaderLog(ShaderType::Fragment);
        std::abort();
    }

    if (!m_shader->compile())
    {
        std::clog << "Failed to load program." << std::endl;
        std::clog << m_shader->getProgramLog();
        std::abort();
    }
}

void SilverGame::update(sf::Time deltaTime)
{
    getRenderer().clear(sf::Color::Black);

    std::clog << "Ligma balls " << deltaTime.asMicroseconds() / 1000.f << std::endl;

    sf::View view({0, 0}, {1280, 720});

    glm::mat4 matrix = glm::make_mat4(view.getTransform().getMatrix());

    m_model->render(matrix, nullptr, m_shader.get());

    getWindow().display();
}

void SilverGame::cleanup()
{
}

} // namespace silver