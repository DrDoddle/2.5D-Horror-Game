#pragma once

#include <string>

enum class TokenType {
    Identifier,
    String,
    Number,

    LeftBrace, // {
    RightBrace, // }
    Equals, // =
    Semicolon, // ;

    EndOfFile,
    Invalid
};

struct Token {
    TokenType type;
    std::string value;

    // Optional, but you'll be VERY happy you have these when
    // the parser eventually says "error on line 47".
    unsigned line = 1;
    unsigned column = 1;
};
