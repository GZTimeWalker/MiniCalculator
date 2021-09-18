#include <string>
#include <iostream>
#include "Lexer.h"

namespace MiniCalculator
{
	Lexer::Lexer(const std::string& source)
	{
		Current = 0;
		Length = source.length();
		Source = source;
	}

	std::vector<Token> Lexer::GetTokens()
	{
		do
		{
			try {
				auto token = Advance();
				if (token.Type != TokenType::NONE)
					Tokens.push_back(token);
				else if(!Finished())
					throw UnexpectedTokenException(token.Start);
			}
			catch(Exception e) {
				throw;
			}
		} while (!Finished());

		return Tokens;
	}

	bool Lexer::Match(char toMatch)
	{
		return Match([&](char chr) -> bool {return chr == toMatch; });
	}

	bool Lexer::Match(std::vector<char> chrs)
	{
		return Match([&](char chr) -> bool {
			bool res = false;
			for (auto& _chr : chrs)
				res = res || (chr == _chr);
			return res;
			});
	}

	bool Lexer::Match(std::function<bool(char)> cond)
	{
		if (Finished())
			return false;

		if (cond(Source[Current]))
		{
			++Current;
			return true;
		}

		return false;
	}


	bool Lexer::Finished() const
	{
		return Current == Length;
	}

	Token Lexer::Advance()
	{
		// skip all space
		while (Match(isspace));
		
		// match single char
		if (Match('('))
			return Token(TokenType::LEFT_PAREN, Current - 1, Current);

		if (Match(')'))
			return Token(TokenType::RIGHT_PAREN, Current - 1, Current);

		if (Match('+'))
			return Token(TokenType::PLUS, Current - 1, Current);

		if (Match('-'))
			return Token(TokenType::MINUS, Current - 1, Current);

		if (Match('*'))
			return Token(TokenType::STAR, Current - 1, Current);
		
		// match monomial
		unsigned int start = Current;

		if (!Match({ 'x' , 'x' }))
		{
			while (Match(isdigit));

			// match float
			if (Match('.'))
				while (Match(isdigit));

			if (start == Current)
				return Token(TokenType::NONE, start, Current++);
			
			// match constant
			if (!Match({ 'x' , 'x' }))
				return Token(TokenType::MONOMIAL, start, Current);
		}

		// match ax / x
		if(!Match('^'))
			return Token(TokenType::MONOMIAL, start, Current);

		if(Match(isspace))
			return Token(TokenType::NONE, start, Current);
		
		// match ax^b / x^c
		while (Match(isdigit));

		return Token(TokenType::MONOMIAL, start, Current);
	}
}


