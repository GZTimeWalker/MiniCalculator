#pragma once

#include "Token.h"
#include <string>
#include <vector>
#include "Expr.h"

namespace MiniCalculator
{
	class Parser
	{
	private:
		std::vector<Token>::const_iterator Begin;
		std::vector<Token>::const_iterator End;
		std::vector<Token>::const_iterator Current;
		std::string Source;
		
		std::map<std::string, std::shared_ptr<Expr>>* Vars;

		Token Match();
		Token Match(TokenType type);
		bool Peek(TokenType type);

		/// <summary>
		/// => MonomialExpr | GroupingExpr
		/// </summary>
		std::shared_ptr<Expr> GetBaseExpr();
		/// <summary>
		/// => UnaryExpr
		/// </summary>
		std::shared_ptr<Expr> GetUnaryExpr();
		/// <summary>
		/// => BinaryExpr (*, nothing)
		/// </summary>
		std::shared_ptr<Expr> GetMutiExpr();
		/// <summary>
		/// => BinaryExpr (+, -)
		/// </summary>
		std::shared_ptr<Expr> GetPlusExpr();

	public:
		Parser(const std::vector<Token>& tokens, std::string& source, std::map<std::string, std::shared_ptr<Expr>>* vars);
		std::shared_ptr<Expr> GenExpr();
	};
}

