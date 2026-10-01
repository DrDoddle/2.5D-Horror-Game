#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

class Player {
public:
    void update(float deltaTime);

    [[nodiscard]] sf::Vector3f position() const;

    [[nodiscard]] sf::Vector2f direction() const;

    void setPosition(const sf::Vector3f &pos);

    void setDirection(float angle);

public:
private:
    sf::Vector3f m_position;
    float m_angle = 0.0f;

    int m_health = 100;
    int m_armor = 0;
};
