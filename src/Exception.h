#pragma once

#include <string>
#include <iostream>

namespace MiniCalculator
{
    /// <summary>
    /// �쳣����
    /// </summary>
    class Exception
    {
    public:
        /// <summary>
        /// �쳣������λ��
        /// </summary>
        size_t pos;
        /// <summary>
        /// �쳣����������
        /// 0  -> pos��
        /// 1 -> �ı�ĩβ
        /// 2 -> ��֧���ı�׷��
        /// </summary>
        int type = 0;
        /// <summary>
        /// �쳣���������
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
    /// �﷨����
    /// </summary>
    class SyntaxException : public Exception {
    public:
        SyntaxException(size_t pos): Exception("Syntax Exception", pos) {}
    };

    /// <summary>
    /// ����֮��� Token
    /// </summary>
    class UnexpectedTokenException : public Exception {
    public:
        UnexpectedTokenException(size_t pos) : Exception("Unexpected Token", pos) {}
    };

    /// <summary>
    /// ����֮�����ֹ
    /// </summary>
    class UnexpectedEOFException : public Exception {
    public:
        UnexpectedEOFException() : Exception("Unexpected EOF", 0, -1) {}
    };

    /// <summary>
    /// ����֮��ı��ʽ
    /// </summary>
    class UnexpectedExpressionException : public Exception {
    public:
        UnexpectedExpressionException(size_t pos) : Exception("Unexpected Expression", pos) {}
    };

    /// <summary>
    /// ����֮������ָ�ʽ
    /// </summary>
    class UnexpectedNumberException : public Exception {
    public:
        UnexpectedNumberException(size_t pos) : Exception("Unexpected Number", pos) {}
    };

    /// <summary>
    /// ��֧�ֵ���ѧ����
    /// </summary>
    class UnsupportedOperationException : public Exception {
    public:
        UnsupportedOperationException() : Exception("Unsupported Operation", 0, -2) {}
    };

    /// <summary>
    /// �Ƿ�������
    /// </summary>
    class IllegalVarNameException : public Exception {
    public:
        IllegalVarNameException(size_t pos) : Exception("Illegal Variable Name", pos) {}
    };
}


