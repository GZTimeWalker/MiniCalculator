#pragma once

#include <string>
#include <iostream>

namespace MiniCalculator
{
	class Exception
	{
	public:
		int pos;
		std::string descr;

	public:
		Exception(std::string descr, int pos) : descr(descr), pos(pos){}

		friend std::ostream& operator<<(std::ostream& out, const Exception& e)
		{
			out << e.descr << " at " << e.pos << std::endl;
			return out;
		}
	};

	class SyntaxException : public Exception {
	public:
		SyntaxException(int pos): Exception("Syntax Exception", pos) {}
	};

	class UnexpectedTokenException : public Exception {
	public:
		UnexpectedTokenException(int pos) : Exception("Unexpected Token", pos) {}
	};

	class UnexpectedEOFException : public Exception {
	public:
		UnexpectedEOFException() : Exception("Unexpected EOF", -1) {}
	};

	class UnexpectedExpressionException : public Exception {
	public:
		UnexpectedExpressionException(int pos) : Exception("Unexpected Expression", pos) {}
	};

	class UnexpectedNumberException : public Exception {
	public:
		UnexpectedNumberException(int pos) : Exception("Unexpected Number", pos) {}
	};
}


