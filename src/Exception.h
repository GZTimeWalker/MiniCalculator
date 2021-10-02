#pragma once

#include <string>
#include <iostream>

namespace MiniCalculator
{
    /// <summary>
    /// 异常基类
    /// </summary>
    class Exception
    {
    public:
        /// <summary>
        /// 异常发生的位置
        /// </summary>
        size_t pos;
        /// <summary>
        /// 异常发生的种类
        /// 0  -> pos处
        /// 1 -> 文本末尾
        /// 2 -> 不支持文本追踪
        /// </summary>
        int type = 0;
        /// <summary>
        /// 异常的相关描述
        /// </summary>
        std::string descr;

    public:
        Exception(std::string descr, size_t pos, int type = 0) : descr(descr), pos(pos){}

        friend std::ostream& operator<<(std::ostream& out, const Exception& e)
        {
            out << e.descr << " at " << e.pos << std::endl;
            return out;
        }
    };

    /// <summary>
    /// 语法错误
    /// </summary>
    class SyntaxException : public Exception {
    public:
        SyntaxException(size_t pos): Exception("Syntax Exception", pos) {}
    };

    /// <summary>
    /// 意料之外的 Token
    /// </summary>
    class UnexpectedTokenException : public Exception {
    public:
        UnexpectedTokenException(size_t pos) : Exception("Unexpected Token", pos) {}
    };

    /// <summary>
    /// 意料之外的终止
    /// </summary>
    class UnexpectedEOFException : public Exception {
    public:
        UnexpectedEOFException() : Exception("Unexpected EOF", 0, -1) {}
    };

    /// <summary>
    /// 意料之外的表达式
    /// </summary>
    class UnexpectedExpressionException : public Exception {
    public:
        UnexpectedExpressionException(size_t pos) : Exception("Unexpected Expression", pos) {}
    };

    /// <summary>
    /// 意料之外的数字格式
    /// </summary>
    class UnexpectedNumberException : public Exception {
    public:
        UnexpectedNumberException(size_t pos) : Exception("Unexpected Number", pos) {}
    };

    /// <summary>
    /// 不支持的数学运算
    /// </summary>
    class UnsupportedOperationException : public Exception {
    public:
        UnsupportedOperationException() : Exception("Unsupported Operation", 0, -2) {}
    };

    /// <summary>
    /// 非法变量名
    /// </summary>
    class IllegalVarNameException : public Exception {
    public:
        IllegalVarNameException(size_t pos) : Exception("Illegal Variable Name", pos) {}
    };
}


