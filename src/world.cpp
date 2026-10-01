#include "world.h"
#include <algorithm>
#include <iostream>

Map &World::map() {
    return m_map;
}

void World::initPlayer(Player &player) {
    auto it = std::find_if(m_map.things.begin(), m_map.things.end(), [](const Thing &t) {
        return t.type == 1;
    });

    // 1. Always verify the Thing was actually found in the map
    if (it != m_map.things.end()) {
        // 2. Set the player's position to the Thing's coordinates
        player.setPosition({it->x, it->y, it->z});
        player.setDirection(it->angle);

        // Optional: If your player tracks orientation, you can copy the angle too
        // player.angle = it->angle;
    } else {
        // 3. Fallback/Error handling if type 1 (Player Spawn) is missing from the map
        std::cerr << "Warning: Map does not contain a Player Spawn (Thing type 1). Setting default position.\n";
        player.setPosition({0, 0, 0});
        player.setDirection(0);
    }
}

const Map &World::map() const {
    return m_map;
}
