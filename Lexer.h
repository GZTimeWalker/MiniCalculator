#pragma once

#include <string>
#include <vector>
#include <cctype>
#include <functional>
#include "Token.h"

namespace MiniCalculator
{
	class Lexer
	{
	private:
		std::string Source;
		std::vector<Token> Tokens;
		unsigned int Current;
		unsigned int Length;
		bool Match(char toMatch);
		bool Match(std::vector<char> chrs);
		bool Match(std::function<bool(char)> cond);
		bool Finished() const;
		Token Advance();

	public:
		explicit Lexer(const std::string& source);
		std::vector<Token> GetTokens();
	};
}
