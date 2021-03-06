#pragma once

#include <string>
#include <map>
#include "Utils.h"

namespace MiniCalculator
{
    /// <summary>
    /// Token ????
    /// </summary>
    enum class TokenType {
        /// <summary>
        /// ??????
        /// </summary>
        LEFT_PAREN,
        /// <summary>
        /// ??????
        /// </summary>
        RIGHT_PAREN,
        /// <summary>
        /// δ֪??
        /// </summary>
        X,
        /// <summary>
        /// ????
        /// </summary>
        NUMBER,
        /// <summary>
        /// ?Ӻ? +
        /// </summary>
        PLUS,
        /// <summary>
        /// ???? -
        /// </summary>
        MINUS,
        /// <summary>
        /// ?Ǻţ??˺ţ? *
        /// </summary>
        STAR,
        /// <summary>
        /// ?˷??? ^
        /// </summary>
        TIP,
        /// <summary>
        /// ???? /
        /// </summary>
        SLASH,
        /// <summary>
        /// ?󵼷??ŵ????? '
        /// </summary>
        RSQUO,
        /// <summary>
        /// ????
        /// </summary>
        VAR,
        /// <summary>
        /// ??
        /// </summary>
        NONE
    };

    class Token {
    public:
        /// <summary>
        /// ??ʼλ??
        /// </summary>
        size_t Start;
        /// <summary>
        /// ????λ??
        /// </summary>
        size_t End;
        /// <summary>
        /// Token????
        /// </summary>
        TokenType Type;

        std::string GetValue(std::string& source) {
            return source.substr(Start, End - Start);
        }

        std::string GetValueWithType(std::string& source) {
            return source.substr(Start, End - Start) + "\t (" + Utils::GetTypeString(Type) + ")";
        }

        Token(TokenType type, size_t start, size_t end) :  Start(start), End(end), Type(type){}
    };
}

