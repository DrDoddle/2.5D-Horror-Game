#pragma once

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>

class FrameBuffer
{
public:
    FrameBuffer(unsigned width, unsigned height);

    void clear(sf::Color color);
    void setPixel(unsigned x, unsigned y, sf::Color color);
    void update();

    sf::Texture &texture();

private:
    sf::Image m_image;
    sf::Texture m_texture;
};