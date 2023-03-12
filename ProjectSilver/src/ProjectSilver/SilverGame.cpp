#include <SFML/Graphics/Vertex.hpp>

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
    "FragColor = Color * texture(tex, TexCoord);"
    "}";

const std::string vs_code =
    "#version 400\n"

    "layout(location = 0) in vec2 aPos;"
    "layout(location = 1) in vec4 aColor;"
    "layout(location = 2) in vec2 aTexCoord;"

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
    std::array vertices = {sf::Vertex({0, 0}, sf::Color::White, {0, 0}),
                           sf::Vertex({0, 100}, sf::Color::White, {0, 0}),
                           sf::Vertex({100, 100}, sf::Color::White, {0, 0})};

    m_texture = getRenderer().createTexture();

    if (!m_texture->loadFromFile("WallTile.png"))
    {
        std::clog << "Failed to load texture." << std::endl;
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

    getSpriteBatch().setView({{0, 0}, {1280, 720}});
}

void SilverGame::update(sf::Time deltaTime)
{
    getRenderer().clear(sf::Color::Black);

    std::clog << "Ligma balls " << deltaTime.asMicroseconds() / 1000.f << std::endl;

    getSpriteBatch().drawSprite(*m_texture,
                                sf::Vector2f(0, 0),
                                sf::radians(0),
                                sf::Vector2f(1, 1),
                                sf::Vector2f(50, 50),
                                sf::Color::Green,
                                m_shader.get());

    getSpriteBatch().drawSprite(*m_texture,
                                sf::Vector2f(200, 300),
                                sf::radians(0),
                                sf::Vector2f(1, 1),
                                sf::Vector2f(0, 0),
                                sf::Color::Green,
                                m_shader.get());

    getSpriteBatch().flush();

    getWindow().display();
}

void SilverGame::cleanup()
{
}

} // namespace silver