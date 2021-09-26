#pragma once

#include <string>
#include <map>
#include "Utils.h"

namespace MiniCalculator
{
    /// <summary>
    /// Token 类型
    /// </summary>
    enum class TokenType {
        /// <summary>
        /// 左括号
        /// </summary>
        LEFT_PAREN,
        /// <summary>
        /// 右括号
        /// </summary>
        RIGHT_PAREN,
        /// <summary>
        /// 未知数
        /// </summary>
        X,
        /// <summary>
        /// 数字
        /// </summary>
        NUMBER,
        /// <summary>
        /// 加号 +
        /// </summary>
        PLUS,
        /// <summary>
        /// 减号 -
        /// </summary>
        MINUS,
        /// <summary>
        /// 星号（乘号） *
        /// </summary>
        STAR,
        /// <summary>
        /// 乘方号 ^
        /// </summary>
        TIP,
        /// <summary>
        /// 除号 /
        /// </summary>
        SLASH,
        /// <summary>
        /// 求导符号单引号 '
        /// </summary>
        RSQUO,
        /// <summary>
        /// 变量
        /// </summary>
        VAR,
        /// <summary>
        /// 空
        /// </summary>
        NONE
    };

    class Token {
    public:
        /// <summary>
        /// 起始位置
        /// </summary>
        unsigned int Start;
        /// <summary>
        /// 结束位置
        /// </summary>
        unsigned int End;
        /// <summary>
        /// Token类型
        /// </summary>
        TokenType Type;

        std::string GetValue(std::string& source) {
            return source.substr(Start, End - Start);
        }

        std::string GetValueWithType(std::string& source) {
            return source.substr(Start, End - Start) + "\t (" + Utils::GetTypeString(Type) + ")";
        }

        Token(TokenType type, unsigned int start, unsigned int end) :  Start(start), End(end), Type(type){}
    };
}

