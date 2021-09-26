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
		/// -1 -> 文本末尾
		/// -2 -> 不支持文本追踪
		/// </summary>
		int pos;
		/// <summary>
		/// 异常的相关描述
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
	/// 语法错误
	/// </summary>
	class SyntaxException : public Exception {
	public:
		SyntaxException(int pos): Exception("Syntax Exception", pos) {}
	};

	/// <summary>
	/// 意料之外的 Token
	/// </summary>
	class UnexpectedTokenException : public Exception {
	public:
		UnexpectedTokenException(int pos) : Exception("Unexpected Token", pos) {}
	};

	/// <summary>
	/// 意料之外的终止
	/// </summary>
	class UnexpectedEOFException : public Exception {
	public:
		UnexpectedEOFException() : Exception("Unexpected EOF", -1) {}
	};

	/// <summary>
	/// 意料之外的表达式
	/// </summary>
	class UnexpectedExpressionException : public Exception {
	public:
		UnexpectedExpressionException(int pos) : Exception("Unexpected Expression", pos) {}
	};

	/// <summary>
	/// 意料之外的数字格式
	/// </summary>
	class UnexpectedNumberException : public Exception {
	public:
		UnexpectedNumberException(int pos) : Exception("Unexpected Number", pos) {}
	};

	/// <summary>
	/// 不支持的数学运算
	/// </summary>
	class UnsupportedOperationException : public Exception {
	public:
		UnsupportedOperationException(int pos) : Exception("Unsupported Operation", pos) {}
	};

	/// <summary>
	/// 非法变量名
	/// </summary>
	class IllegalVarNameException : public Exception {
	public:
		IllegalVarNameException(int pos) : Exception("Illegal Variable Name", pos) {}
	};
}


