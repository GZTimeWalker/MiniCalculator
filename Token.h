#pragma once

#include <string>
#include <map>

namespace MiniCalculator
{
	/// <summary>
	/// Token ¿‡–Õ
	/// </summary>
	enum class TokenType {
		/// <summary>
		/// ◊Û¿®∫≈
		/// </summary>
		LEFT_PAREN,
		/// <summary>
		/// ”“¿®∫≈
		/// </summary>
		RIGHT_PAREN,
		/// <summary>
		/// µ•œÓ Ω
		/// </summary>
		MONOMIAL,
		/// <summary>
		/// º”∫≈ +
		/// </summary>
		PLUS,
		/// <summary>
		/// ºı∫≈ -
		/// </summary>
		MINUS,
		/// <summary>
		/// –«∫≈£®≥À∫≈£© *
		/// </summary>
		STAR,
		/// <summary>
		/// ±‰¡ø
		/// </summary>
		VAR,
		/// <summary>
		/// ø’
		/// </summary>
		NONE,
	};

	class Token {
	public:
		unsigned int Start;
		unsigned int End;
		TokenType Type;

		std::string GetValue(std::string& source) {
			return source.substr(Start, End - Start);
		}

		std::string GetValueWithType(std::string& source) {
			return source.substr(Start, End - Start) + "\t (" + GetTypeString() + ")";
		}

		std::string GetTypeString()
		{
			switch (Type)
			{
			case MiniCalculator::TokenType::LEFT_PAREN:
				return "Left Paren";
			case MiniCalculator::TokenType::RIGHT_PAREN:
				return "Right Paren";
			case MiniCalculator::TokenType::MONOMIAL:
				return "Monomial";
			case MiniCalculator::TokenType::PLUS:
				return "Plus";
			case MiniCalculator::TokenType::MINUS:
				return "Minus";
			case MiniCalculator::TokenType::STAR:
				return "Star";
			case MiniCalculator::TokenType::NONE:
			default:
				return "Unknown";
			}
		}

		Token(TokenType type, unsigned int start, unsigned int end) :  Start(start), End(end), Type(type){}
	};
}

