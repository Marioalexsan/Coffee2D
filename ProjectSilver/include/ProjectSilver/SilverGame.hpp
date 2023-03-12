#pragma once
#include <Coffee2D/Game/Game.hpp>
#include <Coffee2D/Graphics/Renderer.hpp>

namespace silver
{
class SilverGame : public coffee::Game
{
    std::unique_ptr<coffee::Model2D> m_model;
    std::unique_ptr<coffee::Shader> m_shader;

public:
    void initialize() override;

    void update(sf::Time deltaTime) override;

    void cleanup() override;
};
} // namespace silver