#pragma once

#include "map.h"
#include "player.h"

class World {
public:
    Map &map();

    void initPlayer(Player &player);

    const Map &map() const;

private:
    Map m_map;
};
