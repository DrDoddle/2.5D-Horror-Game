#include "udmflexer.h"

UdmfLexer::UdmfLexer(std::string source)
    : m_source(std::move(source)), m_index(0) {
}

std::vector<Token> UdmfLexer::tokenize() {
    std::vector<Token> tokens;

    while (peek().has_value()) {
        char c = peek().value();

        // Whitespace
        if (std::isspace(static_cast<unsigned char>(c))) {
            consume();
            continue;
        }

        if (c == '/' && peek(1).has_value() && peek(1).value() == '/')
        {
            consume();
            consume();

            while (peek().has_value() && peek().value() != '\n')
                consume();

            continue;
        }

        // Single-character tokens
        if (c == '{') {
            consume();
            tokens.push_back({TokenType::LeftBrace, "{"});
            continue;
        }

        if (c == '}') {
            consume();
            tokens.push_back({TokenType::RightBrace, "}"});
            continue;
        }

        if (c == '=') {
            consume();
            tokens.push_back({TokenType::Equals, "="});
            continue;
        }

        if (c == ';') {
            consume();
            tokens.push_back({TokenType::Semicolon, ";"});
            continue;
        }

        // String
        if (c == '"') {
            consume();

            std::string value;

            while (peek().has_value() && peek().value() != '"')
                value += consume();

            if (!peek().has_value()) {
                tokens.push_back({TokenType::Invalid, value});
                break;
            }

            consume(); // closing "

            tokens.push_back({TokenType::String, value});
            continue;
        }

        // Number
        if (std::isdigit(static_cast<unsigned char>(c)) ||
            c == '-' || c == '.') {
            std::string value;

            while (peek().has_value()) {
                char n = peek().value();

                if (std::isdigit(static_cast<unsigned char>(n)) ||
                    n == '.' || n == '-') {
                    value += consume();
                } else {
                    break;
                }
            }

            tokens.push_back({TokenType::Number, value});
            continue;
        }

        // Identifier
        if (std::isalpha(static_cast<unsigned char>(c)) || c == '_') {
            std::string value;

            while (peek().has_value()) {
                char n = peek().value();

                if (std::isalnum(static_cast<unsigned char>(n)) || n == '_')
                    value += consume();
                else
                    break;
            }

            tokens.push_back({TokenType::Identifier, value});
            continue;
        }

        // Unknown character
        tokens.push_back({TokenType::Invalid, std::string(1, consume())});
    }

    tokens.push_back({TokenType::EndOfFile, ""});

    return tokens;
}

std::optional<char> UdmfLexer::peek(const size_t offset) const {
    if (m_index + offset >= m_source.length())
        return {};
    return m_source.at(m_index + offset);
}


char UdmfLexer::consume() {
    return m_source.at(m_index++);
}
