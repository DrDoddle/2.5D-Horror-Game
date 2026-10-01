#pragma once

#include "framebuffer.h"
#include "player.h"
#include "world.h"

class Renderer {
public:
    Renderer(unsigned width, unsigned height);

    void render(World &world, const Player &player);

    sf::Texture &texture();

private:
    FrameBuffer m_framebuffer;
};
