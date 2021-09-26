#pragma once

#include <string>
#include <vector>
#include <cctype>
#include <functional>
#include "Token.h"

namespace MiniCalculator
{
    /// <summary>
    /// �ʷ�������
    /// </summary>
    class Lexer
    {
    private:
        /// <summary>
        /// Դ�ַ���
        /// </summary>
        std::string Source;
        /// <summary>
        /// Tokens
        /// </summary>
        std::vector<Token> Tokens;
        /// <summary>
        /// ��ǰλ��
        /// </summary>
        size_t Current;
        /// <summary>
        /// �ַ�������
        /// </summary>
        size_t Length;
        /// <summary>
        /// ƥ��һ���ַ�
        /// </summary>
        /// <param name="toMatch">�ڴ����ַ�</param>
        /// <returns>�Ƿ�ƥ��</returns>
        bool Match(char toMatch);
        /// <summary>
        /// ƥ��һϵ���ַ�
        /// </summary>
        /// <param name="chrs">�ڴ��Ŀ����ַ�</param>
        /// <returns>�Ƿ�ƥ��</returns>
        bool Match(std::vector<char> chrs);
        /// <summary>
        /// ���պ���ƥ���ַ�
        /// </summary>
        /// <param name="cond">����</param>
        /// <returns>�Ƿ�ƥ��</returns>
        bool Match(std::function<bool(char)> cond);
        /// <summary>
        /// �Ƿ�ƥ�����
        /// </summary>
        /// <returns></returns>
        bool Finished() const;
        /// <summary>
        /// ��ȡ��һ��Token
        /// </summary>
        /// <returns>��һ��Token</returns>
        Token Advance();

    public:
        explicit Lexer(const std::string& source);
        /// <summary>
        /// ��ȡ�ַ�����Token
        /// </summary>
        /// <returns>Token�б�</returns>
        std::vector<Token> GetTokens();
    };
}
