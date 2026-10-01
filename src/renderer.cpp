#include "renderer.h"

#include <cstdint>
#include <cmath>
#include <algorithm>

Renderer::Renderer(const unsigned width, const unsigned height)
    : m_framebuffer(width, height) {
}

void Renderer::render(World &world, const Player &player) {
    m_framebuffer.clear(sf::Color::Black);

    const sf::Vector2u size = m_framebuffer.texture().getSize();
    const float width = static_cast<float>(size.x);
    const float height = static_cast<float>(size.y);
    const float distToScreen = width / 2.f;
    const float horizon = height / 2.f;

    const sf::Vector2f playerPos{player.position().x, player.position().y};
    const sf::Vector2f dir = player.direction();

    // World to Camera space transformation
    auto toCameraSpace = [&](const Vertex &v) {
        sf::Vector2f rel = v - playerPos;
        return sf::Vector2f{
            rel.y * dir.x - rel.x * dir.y, // Camera X (Right)
            rel.x * dir.x + rel.y * dir.y // Camera Y (Forward Depth)
        };
    };

    const auto &map = world.map();

    for (const auto &line: map.linedefs) {
        sf::Vector2f p1 = toCameraSpace(map.vertices[line.v1]);
        sf::Vector2f p2 = toCameraSpace(map.vertices[line.v2]);

        // Skip linedefs fully behind the camera near plane
        if (p1.y <= 0.1f && p2.y <= 0.1f)
            continue;

        // Clip against near plane (y = 0.1f)
        if (p1.y <= 0.1f || p2.y <= 0.1f) {
            float t = (0.1f - p1.y) / (p2.y - p1.y);
            sf::Vector2f clipped = p1 + t * (p2 - p1);
            if (p1.y <= 0.1f) p1 = clipped;
            else p2 = clipped;
        }

        // Project X coordinates
        int x1 = static_cast<int>((p1.x * distToScreen / p1.y) + (width / 2.f));
        int x2 = static_cast<int>((p2.x * distToScreen / p2.y) + (width / 2.f));

        // Ensure left-to-right processing order
        if (x1 > x2) {
            std::swap(x1, x2);
            std::swap(p1, p2);
        }

        int startX = std::clamp(x1, 0, static_cast<int>(width) - 1);
        int endX = std::clamp(x2, 0, static_cast<int>(width) - 1);

        for (int x = startX; x <= endX; ++x) {
            float factor = (x1 == x2)
                               ? 0.f
                               : static_cast<float>(x - x1) / (x2 - x1);

            float invY1 = 1.f / p1.y;
            float invY2 = 1.f / p2.y;

            float invY =
                    invY1 + factor * (invY2 - invY1);

            float currentY = 1.f / invY;

            constexpr float WALL_HEIGHT = 128.f;

            int wallHeight = static_cast<int>(
                WALL_HEIGHT * distToScreen / currentY
            );

            int yStart = std::clamp(
                static_cast<int>(horizon - wallHeight / 2.f),
                0,
                static_cast<int>(height) - 1
            );

            int yEnd = std::clamp(
                static_cast<int>(horizon + wallHeight / 2.f),
                0,
                static_cast<int>(height) - 1
            );

            for (int y = yStart; y <= yEnd; ++y)
                m_framebuffer.setPixel(x, y, sf::Color::Yellow);
        }
    }

    m_framebuffer.update();
}

sf::Texture &Renderer::texture() {
    return m_framebuffer.texture();
}
