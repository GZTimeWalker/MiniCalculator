#pragma once

#include <string>
#include <vector>

#include "Token.h"


namespace MiniCalculator
{
	class Expr;
	/// <summary>
	/// �﷨������
	/// </summary>
	class Parser
	{
	private:
		/// <summary>
		/// Token ��ʼ������
		/// </summary>
		std::vector<Token>::const_iterator Begin;
		/// <summary>
		/// Token ��ֹ������
		/// </summary>
		std::vector<Token>::const_iterator End;
		/// <summary>
		/// Token ��ǰ������
		/// </summary>
		std::vector<Token>::const_iterator Current;
		/// <summary>
		/// Դ�ַ���
		/// </summary>
		std::string Source;
		
		/// <summary>
		/// ����ӳ��ָ��
		/// </summary>
		std::map<std::string, std::shared_ptr<Expr>>* Vars;

		/// <summary>
		/// ��ȡһ��Token
		/// </summary>
		/// <returns>Token</returns>
		Token Match();
		/// <summary>
		/// ��ȡһ��ָ�����͵�Token
		/// </summary>
		/// <param name="type">ָ��������</param>
		/// <returns>Token</returns>
		Token Match(TokenType type);
		/// <summary>
		/// �жϵ�ǰλ���ǲ���ĳ�����͵�Token
		/// </summary>
		/// <param name="type">Token����</param>
		/// <returns>�Ƿ�ƥ��</returns>
		bool Peek(TokenType type);
		/// <summary>
		/// �жϵ�ǰ����λ���ǲ���ĳ�����͵�Token
		/// </summary>
		/// <param name="type">Token����</param>
		/// <param name="next">��һλToken����</param>
		/// <returns>�Ƿ�ƥ��</returns>
		bool Peek(TokenType type, TokenType next);

		/// <summary>
		/// => MonomialExpr | GroupingExpr | Expr ( Expr )
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
		/// <summary>
		/// �����﷨��
		/// </summary>
		std::shared_ptr<Expr> GenExpr();
	};
}
