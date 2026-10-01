//
// Created by joshu on 9/30/2026.
//

#include "udmfparser.h"

UdmfParser::UdmfParser(std::vector<Token> tokens)
    : m_tokens(std::move(tokens)), m_index(0) {
}

void UdmfParser::parseVertex(Map &map) {
    Vertex vertex;
    consume(); // vertex
    consume(); // {
    while (peek().has_value() && peek().value().type != TokenType::RightBrace) {
        Token property = consume();
        if (property.value == "x") {
            consume(); // =
            vertex.x = std::stof(consume().value);
            consume(); // ;
        } else if (property.value == "y") {
            consume(); // =
            vertex.y = std::stof(consume().value);
            consume(); // ;
        } else {
            // Robustly skip unhandled fields: "property_name = value;"
            consume(); // consume '='
            consume(); // consume the value token
            consume(); // consume ';'
        }
    }
    consume(); // }
    map.vertices.push_back(vertex);
}

void UdmfParser::parseThing(Map &map) {
    Thing thing;
    consume(); // thing
    consume(); // {
    while (peek().has_value() && peek().value().type != TokenType::RightBrace) {
        Token property = consume();
        if (property.value == "x") {
            consume(); // =
            thing.x = std::stof(consume().value);
            consume(); // ;
        } else if (property.value == "y") {
            consume(); // =
            thing.y = std::stof(consume().value);
            consume(); // ;
        } else if (property.value == "angle") {
            consume(); // =
            thing.angle = std::stof(consume().value);
            consume(); // ;
        } else if (property.value == "type") {
            consume(); // =
            thing.type = std::stoi(consume().value);
            consume(); // ;
        } else {
            consume(); // consume '='
            consume(); // consume the value token
            consume(); // consume ';'
        }
    }
    consume(); // }
    map.things.push_back(thing);
}

void UdmfParser::parseLinedef(Map &map) {
    Linedef linedef;
    consume(); // linedef
    consume(); //  {
    while (peek().has_value() &&
           peek().value().type != TokenType::RightBrace) {
        Token property = consume();
        if (property.value == "v1") {
            consume(); // =
            linedef.v1 = std::stoi(consume().value);
            consume(); // ;
        } else if (property.value == "v2") {
            consume(); // =
            linedef.v2 = std::stoi(consume().value);
            consume(); // ;
        } else if (property.value == "sidefront") {
            consume(); // =
            linedef.front = std::stoi(consume().value);
            consume(); // ;
        } else if (property.value == "sideback") {
            consume(); // =
            linedef.back = std::stoi(consume().value);
            consume(); // ;
        } else if (property.value == "blocking") {
            consume(); // =
            linedef.blocking = (consume().value == "true");
            consume(); // ;
        } else if (property.value == "twosided") {
            consume(); // =
            linedef.isTwoSided = (consume().value == "true");
            consume(); // ;
        }
    }

    consume(); // }
    map.linedefs.push_back(linedef);
}

void UdmfParser::parseSidedef(Map &map) {
    Sidedef sidedef;
    consume(); // sidedef
    consume(); // =
    while (peek().has_value() && peek().value().type != TokenType::RightBrace) {
        Token property = consume();
        if (property.value == "sector") {
            consume(); // =
            sidedef.sector = std::stoi(consume().value);
            consume(); // ;
        } else if (property.value == "texturebottom") {
            consume(); // =
            sidedef.bottomTexture = consume().value;
            consume(); // ;
        } else if (property.value == "texturemiddle") {
            consume(); // =
            sidedef.midTexture = consume().value;
            consume(); // ;
        } else if (property.value == "texturetop") {
            consume(); // =
            sidedef.topTexture = consume().value;
            consume(); // ;
        } else {
            consume(); // consume '='
            consume(); // consume the value token
            consume(); // consume ';'
        }
    }
    consume(); // }
    map.sidedefs.push_back(sidedef);
}

void UdmfParser::parseNameSpace(Map &map) {
    consume(); // namespace
    consume(); // =
    consume(); // "zdoom"
    consume(); // ;
}

void UdmfParser::parseSector(Map &map) {
    Sector sector;
    consume(); // sector
    consume(); // {
    while (peek().has_value() && peek().value().type != TokenType::RightBrace) {
        Token property = consume();
        if (property.value == "heightfloor") {
            consume(); // =
            sector.floorHeight = std::stof(consume().value);
            consume(); //;
        } else if (property.value == "heightceiling") {
            consume(); // =
            sector.ceilingHeight = std::stof(consume().value);
            consume(); //;
        } else if (property.value == "texturefloor") {
            consume(); // =
            sector.floorTexture = consume().value;
            consume(); //;
        } else if (property.value == "textureceiling") {
            consume(); // =
            sector.ceilingTexture = consume().value;
            consume(); //;
        } else if (property.value == "lightlevel") {
            consume(); // =
            sector.lightLevel = std::stoi(consume().value);
            consume(); //;
        } else {
            consume(); // consume '='
            consume(); // consume the value token
            consume(); // consume ';'
        }
    }

    consume(); // }
    map.sectors.push_back(sector);
}

std::optional<Map> UdmfParser::parse() {
    Map map;
    while (peek().has_value() &&
           peek().value().type != TokenType::EndOfFile) {
        Token token = peek().value();

        if (token.type == TokenType::Identifier) {
            if (token.value == "vertex") {
                parseVertex(map);
            } else if (token.value == "thing") {
                parseThing(map);
            } else if (token.value == "linedef") {
                parseLinedef(map);
            } else if (token.value == "sidedef") {
                parseSidedef(map);
            } else if (token.value == "namespace") {
                parseNameSpace(map);
            } else if (token.value == "sector") {
                parseSector(map);
            }
        }
    }

    for (auto &linedef: map.linedefs) {
        linedef.calculateBounds(map.vertices);
    }

    return map;
}

std::optional<Token> UdmfParser::peek(const int offset) {
    if (m_index + offset >= m_tokens.size()) {
        return {};
    }
    return m_tokens.at(m_index + offset);
}

Token UdmfParser::consume() {
    return m_tokens.at(m_index++);
}
