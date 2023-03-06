#pragma once
#include <Coffee2D/Export.hpp>

namespace coffee
{
class COFFEE2D_API Sprite
{
    virtual Sprite() = 0;

    void getSize();
    void setSize(sf::Vector2);
};
} // namespace coffee