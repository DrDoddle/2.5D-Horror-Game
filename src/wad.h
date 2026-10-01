#pragma once

#include <string>
#include <optional>

class Map;

class MapLoader {
public:
    virtual ~MapLoader() = default;

    virtual std::optional<Map> loadFromFile(const std::string &filepath) = 0;

private:
};

class UdmfMapLoader : MapLoader {
public:
    std::optional<Map> loadFromFile(const std::string &filepath) override;
};
