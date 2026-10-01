#include "player.h"

#include <cmath>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

constexpr float MOVE_SPEED = 100.f;
constexpr float TURN_SPEED = 180.f;

void Player::update(const float deltaTime) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        m_angle += TURN_SPEED * deltaTime;
        if (m_angle >= 360)
            m_angle -= 360;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        m_angle -= TURN_SPEED * deltaTime;
        if (m_angle < 0)
            m_angle += 360;
    }

    sf::Vector3f movement{};
    auto dir = direction();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        movement += {dir.x, dir.y, 0};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        movement -= {dir.x, dir.y, 0};

    // FIXED: Standard 2D Left/Right Perpendicular Strafe Vector signs
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        movement += {-dir.y, dir.x, 0}; // Left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        movement += {dir.y, -dir.x, 0}; // Right

    m_position += movement * MOVE_SPEED * deltaTime;
}

sf::Vector3f Player::position() const {
    return m_position;
}

sf::Vector2f Player::direction() const {
    constexpr float DEG_TO_RAD = 3.14159265359f / 180.f;

    float radians = m_angle * DEG_TO_RAD;

    return {
        std::cos(radians),
        std::sin(radians)
    };
}

void Player::setPosition(const sf::Vector3f &pos) {
    m_position = pos;
}

void Player::setDirection(float angle) {
    m_angle = angle;
}
