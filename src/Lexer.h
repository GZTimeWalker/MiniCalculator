#pragma once

#include <string>
#include <vector>
#include <cctype>
#include <functional>
#include "Token.h"

namespace MiniCalculator
{
    /// <summary>
    /// 词法分析器
    /// </summary>
    class Lexer
    {
    private:
        /// <summary>
        /// 源字符串
        /// </summary>
        std::string Source;
        /// <summary>
        /// Tokens
        /// </summary>
        std::vector<Token> Tokens;
        /// <summary>
        /// 当前位置
        /// </summary>
        size_t Current;
        /// <summary>
        /// 字符串长度
        /// </summary>
        size_t Length;
        /// <summary>
        /// 匹配一个字符
        /// </summary>
        /// <param name="toMatch">期待的字符</param>
        /// <returns>是否匹配</returns>
        bool Match(char toMatch);
        /// <summary>
        /// 匹配一系列字符
        /// </summary>
        /// <param name="chrs">期待的可能字符</param>
        /// <returns>是否匹配</returns>
        bool Match(std::vector<char> chrs);
        /// <summary>
        /// 按照函数匹配字符
        /// </summary>
        /// <param name="cond">函数</param>
        /// <returns>是否匹配</returns>
        bool Match(std::function<bool(char)> cond);
        /// <summary>
        /// 是否匹配结束
        /// </summary>
        /// <returns></returns>
        bool Finished() const;
        /// <summary>
        /// 获取下一个Token
        /// </summary>
        /// <returns>下一个Token</returns>
        Token Advance();

    public:
        explicit Lexer(const std::string& source);
        /// <summary>
        /// 获取字符串的Token
        /// </summary>
        /// <returns>Token列表</returns>
        std::vector<Token> GetTokens();
    };
}
