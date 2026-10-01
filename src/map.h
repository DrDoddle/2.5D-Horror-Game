#pragma once

#include <vector>
#include <string>
#include <memory>
#include <SFML/System/Vector2.hpp>

#include "wad.h"

using Vertex = sf::Vector2f;

struct Sector {
    int id;
    float floorHeight;
    float ceilingHeight;
    std::string floorTexture;
    std::string ceilingTexture;
    int lightLevel; // 0 to 255
};

struct Sidedef {
    int sector; // Sector this side faces
    std::string topTexture;
    std::string midTexture;
    std::string bottomTexture;
    float offsetX, offsetY;
};

struct Linedef {
    int v1; //index of vertex 1
    int v2; //index of vertex 2

    int front;
    int back;

    bool isTwoSided = false;
    bool blocking = true;

    float minX;
    float minY;
    float maxX;
    float maxY;

    void calculateBounds(const std::vector<Vertex> &vertices) {
        const Vertex &a = vertices[v1];
        const Vertex &b = vertices[v2];

        minX = std::min(a.x, b.x);
        maxX = std::max(a.x, b.x);
        minY = std::min(a.y, b.y);
        maxY = std::max(a.y, b.y);
    }
};


struct Thing {
    float x, y, z;
    float angle;
    int type;
    int flags;
};


class Map {
public:
    std::vector<Vertex> vertices;
    std::vector<Sector> sectors;
    std::vector<Linedef> linedefs;
    std::vector<Sidedef> sidedefs;
    std::vector<Thing> things;
};
