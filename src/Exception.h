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
		/// -1 -> �ı�ĩβ
		/// -2 -> ��֧���ı�׷��
		/// </summary>
		int pos;
		/// <summary>
		/// �쳣���������
		/// </summary>
		std::string descr;

	public:
		Exception(std::string descr, int pos) : descr(descr), pos(pos){}

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
		SyntaxException(int pos): Exception("Syntax Exception", pos) {}
	};

	/// <summary>
	/// ����֮��� Token
	/// </summary>
	class UnexpectedTokenException : public Exception {
	public:
		UnexpectedTokenException(int pos) : Exception("Unexpected Token", pos) {}
	};

	/// <summary>
	/// ����֮�����ֹ
	/// </summary>
	class UnexpectedEOFException : public Exception {
	public:
		UnexpectedEOFException() : Exception("Unexpected EOF", -1) {}
	};

	/// <summary>
	/// ����֮��ı��ʽ
	/// </summary>
	class UnexpectedExpressionException : public Exception {
	public:
		UnexpectedExpressionException(int pos) : Exception("Unexpected Expression", pos) {}
	};

	/// <summary>
	/// ����֮������ָ�ʽ
	/// </summary>
	class UnexpectedNumberException : public Exception {
	public:
		UnexpectedNumberException(int pos) : Exception("Unexpected Number", pos) {}
	};

	/// <summary>
	/// ��֧�ֵ���ѧ����
	/// </summary>
	class UnsupportedOperationException : public Exception {
	public:
		UnsupportedOperationException(int pos) : Exception("Unsupported Operation", pos) {}
	};

	/// <summary>
	/// �Ƿ�������
	/// </summary>
	class IllegalVarNameException : public Exception {
	public:
		IllegalVarNameException(int pos) : Exception("Illegal Variable Name", pos) {}
	};
}


