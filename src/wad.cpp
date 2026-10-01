#include "wad.h"
#include <fstream>
#include <iostream>
#include <sstream>

#include "udmflexer.h"
#include "udmfparser.h"
#include "token.h"
#include "map.h"

std::optional<Map> UdmfMapLoader::loadFromFile(const std::string &filepath) {
    std::ifstream file(filepath);

    if (!file)
        return {};

    std::stringstream buffer;
    buffer << file.rdbuf();

    std::string source = buffer.str();

    UdmfLexer lexer(source);
    auto tokens = lexer.tokenize();

    UdmfParser parser(tokens);

    return parser.parse();
}
