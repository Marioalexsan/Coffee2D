#pragma once
#include <Coffee2D/Game/Game.hpp>
#include <Coffee2D/Graphics/Renderer.hpp>

namespace silver
{
class SilverGame : public coffee::Game
{
    std::unique_ptr<coffee::Shader>  m_shader;
    std::unique_ptr<coffee::Texture> m_texture;

    sf::Angle m_angle;

public:
    void initialize() override;

    void update(sf::Time deltaTime) override;

    void cleanup() override;
};
} // namespace silver