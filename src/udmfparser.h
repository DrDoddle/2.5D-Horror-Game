#pragma once

#include <vector>
#include <optional>

#include "token.h"
#include "map.h"
#include <optional>

class UdmfParser {
public:
    UdmfParser(std::vector<Token> tokens);

    std::optional<Map> parse();

private:
    std::vector<Token> m_tokens;

    size_t m_index = 0;

private:
    [[nodiscard]] std::optional<Token> peek(const int offset = 0);

    Token consume();

    void parseVertex(Map &map);

    void parseThing(Map &map);

    void parseLinedef(Map &map);

    void parseSidedef(Map &map);

    void parseNameSpace(Map &map);

    void parseSector(Map &map);
};
