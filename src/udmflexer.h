#pragma once

#include <string>
#include <vector>
#include <optional>
#include "token.h"

class UdmfLexer {
public:
    explicit UdmfLexer(std::string source);

    std::vector<Token> tokenize();

private:
    std::string m_source;

    size_t m_index;

private:
    [[nodiscard]] std::optional<char> peek(const size_t offset = 0) const;

    char consume();
};
