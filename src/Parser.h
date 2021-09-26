#pragma once

#include <string>
#include <vector>

#include "Token.h"


namespace MiniCalculator
{
	class Expr;
	/// <summary>
	/// 语法分析器
	/// </summary>
	class Parser
	{
	private:
		/// <summary>
		/// Token 起始迭代器
		/// </summary>
		std::vector<Token>::const_iterator Begin;
		/// <summary>
		/// Token 终止迭代器
		/// </summary>
		std::vector<Token>::const_iterator End;
		/// <summary>
		/// Token 当前迭代器
		/// </summary>
		std::vector<Token>::const_iterator Current;
		/// <summary>
		/// 源字符串
		/// </summary>
		std::string Source;
		
		/// <summary>
		/// 变量映射指针
		/// </summary>
		std::map<std::string, std::shared_ptr<Expr>>* Vars;

		/// <summary>
		/// 获取一个Token
		/// </summary>
		/// <returns>Token</returns>
		Token Match();
		/// <summary>
		/// 获取一个指定类型的Token
		/// </summary>
		/// <param name="type">指定的类型</param>
		/// <returns>Token</returns>
		Token Match(TokenType type);
		/// <summary>
		/// 判断当前位置是不是某个类型的Token
		/// </summary>
		/// <param name="type">Token类型</param>
		/// <returns>是否匹配</returns>
		bool Peek(TokenType type);
		/// <summary>
		/// 判断当前两个位置是不是某个类型的Token
		/// </summary>
		/// <param name="type">Token类型</param>
		/// <param name="next">下一位Token类型</param>
		/// <returns>是否匹配</returns>
		bool Peek(TokenType type, TokenType next);
		bool Peek(TokenType type, TokenType next, TokenType next1);
		bool Peek(TokenType type, TokenType next, TokenType next1, TokenType next2);

		/// <summary>
		/// => MonomialExpr | GroupingExpr | Expr ( Expr ) | Number
		/// </summary>
		std::shared_ptr<Expr> GetBaseExpr();
		/// <summary>
		/// => DerivativeExpr Expr '
		/// </summary>
		std::shared_ptr<Expr> GetDerivativeExpr();
		/// <summary>
		/// => UnaryExpr (- | +) Expr
		/// </summary>
		std::shared_ptr<Expr> GetUnaryExpr();
		/// <summary>
		/// => PowExpr Expr ^ Expr
		/// </summary>
		std::shared_ptr<Expr> GetPowExpr();
		/// <summary>
		/// => BinaryExpr Expr (* | / | none) Expr
		/// </summary>
		std::shared_ptr<Expr> GetMutiExpr();
		/// <summary>
		/// => BinaryExpr Expr (+ | -) Expr
		/// </summary>
		std::shared_ptr<Expr> GetPlusExpr();

	public:
		Parser(const std::vector<Token>& tokens, std::string& source, std::map<std::string, std::shared_ptr<Expr>>* vars);
		/// <summary>
		/// 生成语法树
		/// </summary>
		std::shared_ptr<Expr> GenExpr();
	};
}

