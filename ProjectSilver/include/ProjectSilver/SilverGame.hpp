#pragma once
#include <Coffee2D/Game/Game.hpp>

namespace silver
{
    class SilverGame : public coffee::Game
    {
        void initialize() override;

        void update(sf::Time deltaTime) override;

        void cleanup() override;
    };
} // namespace silver