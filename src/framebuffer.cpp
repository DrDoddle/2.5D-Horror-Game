#include "framebuffer.h"

FrameBuffer::FrameBuffer(unsigned width, unsigned height)
{
    m_image.resize({width, height}, sf::Color::Black);
    m_texture.resize({width, height});
    
    m_texture.setSmooth(false);
}

void FrameBuffer::clear(sf::Color color)
{
    m_image.resize(m_image.getSize(), color);
}

void FrameBuffer::setPixel(unsigned x, unsigned y, sf::Color color)
{
    if (x >= m_image.getSize().x ||
        y >= m_image.getSize().y)
        return;

    m_image.setPixel({x, y}, color);
}

void FrameBuffer::update()
{
    m_texture.update(m_image);
}

sf::Texture &FrameBuffer::texture()
{
    return m_texture;
}
