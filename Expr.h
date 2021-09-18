#pragma once

#include <memory>
#include "Polyomial.h"
#include "Token.h"

namespace MiniCalculator
{
	/// <summary>
	/// 表达式的基类
	/// </summary>
	class Expr
	{
	public:
		/// <summary>
		/// 计算表达式
		/// </summary>
		/// <returns>返回多项式</returns>
		virtual Polyomial Eval();

		/// <summary>
		/// 计算表达式
		/// </summary>
		/// <param name="poly">多项式</param>
		/// <returns>返回多项式</returns>
		virtual Polyomial Eval(Polyomial poly);

		/// <summary>
		/// 带入自变量计算多项式
		/// </summary>
		/// <param name="x">自变量</param>
		/// <returns>多项式的值</returns>
		virtual double Eval(double x);
	};

	/// <summary>
	/// 二元表达式
	/// </summary>
	class BinaryExpr : public Expr
	{
	private:
		/// <summary>
		/// 左表达式
		/// </summary>
		std::shared_ptr<Expr> Left;
		/// <summary>
		/// 二元运算符
		/// </summary>
		Token Operator;
		/// <summary>
		/// 右表达式
		/// </summary>
		std::shared_ptr<Expr> Right;

	public:
		BinaryExpr(std::shared_ptr<Expr> left, Token _operator, std::shared_ptr<Expr> right) : Left(left), Operator(_operator), Right(right) {}
		/// <summary>
		/// 计算表达式
		/// </summary>
		/// <returns>返回多项式</returns>
		Polyomial Eval() override;
		/// <summary>
		/// 带入自变量计算多项式
		/// </summary>
		/// <param name="x">自变量</param>
		/// <returns>多项式的值</returns>
		double Eval(double x) override;
		/// <summary>
		/// 计算表达式
		/// </summary>
		/// <param name="poly">多项式</param>
		/// <returns>返回多项式</returns>
		Polyomial Eval(Polyomial poly) override;
	};

	/// <summary>
	/// 分组表达式
	/// </summary>
	class GroupingExpr : public Expr
	{
	private:
		/// <summary>
		/// 表达式
		/// </summary>
		std::shared_ptr<Expr> Expression;

	public:
		GroupingExpr(std::shared_ptr<Expr> expression): Expression(expression) {}
		/// <summary>
		/// 计算表达式
		/// </summary>
		/// <returns>返回多项式</returns>
		Polyomial Eval() override;
		/// <summary>
		/// 带入自变量计算多项式
		/// </summary>
		/// <param name="x">自变量</param>
		/// <returns>多项式的值</returns>
		double Eval(double x) override;
		/// <summary>
		/// 计算表达式
		/// </summary>
		/// <param name="poly">多项式</param>
		/// <returns>返回多项式</returns>
		Polyomial Eval(Polyomial poly) override;
	};

	/// <summary>
	/// 复合表达式
	/// </summary>
	class CompoundExpr : public Expr
	{
	private:
		/// <summary>
		/// 基表达式
		/// </summary>
		std::shared_ptr<Expr> Base;

		/// <summary>
		/// 待复合表达式
		/// </summary>
		std::shared_ptr<Expr> Compound;

	public:
		CompoundExpr(std::shared_ptr<Expr> base, std::shared_ptr<Expr> compound) : Base(base), Compound(compound) {}
		/// <summary>
		/// 计算表达式
		/// </summary>
		/// <returns>返回多项式</returns>
		Polyomial Eval() override;
		/// <summary>
		/// 带入自变量计算多项式
		/// </summary>
		/// <param name="x">自变量</param>
		/// <returns>多项式的值</returns>
		double Eval(double x) override;
		/// <summary>
		/// 计算表达式
		/// </summary>
		/// <param name="poly">多项式</param>
		/// <returns>返回多项式</returns>
		Polyomial Eval(Polyomial poly) override;
	};

	/// <summary>
	/// 一元表达式
	/// </summary>
	class UnaryExpr : public Expr
	{
	private:
		/// <summary>
		/// 一元运算符
		/// </summary>
		Token Operator;
		/// <summary>
		/// 右表达式
		/// </summary>
		std::shared_ptr<Expr> Right;
	public:
		UnaryExpr(Token _operator, std::shared_ptr<Expr> right): Operator(_operator), Right(right){}
		/// <summary>
		/// 计算表达式
		/// </summary>
		/// <returns>返回多项式</returns>
		Polyomial Eval() override;
		/// <summary>
		/// 带入自变量计算多项式
		/// </summary>
		/// <param name="x">自变量</param>
		/// <returns>多项式的值</returns>
		double Eval(double x) override;
		/// <summary>
		/// 计算表达式
		/// </summary>
		/// <param name="poly">多项式</param>
		/// <returns>返回多项式</returns>
		Polyomial Eval(Polyomial poly) override;
	};

	/// <summary>
	/// 单项式表达式
	/// </summary>
	class MonomialExpr : public Expr
	{
	private:
		/// <summary>
		/// 系数
		/// </summary>
		double Factor;
		/// <summary>
		/// 指数
		/// </summary>
		int Exponent;
	public:
		MonomialExpr(double factor, int exponent) : Factor(factor), Exponent(exponent) {}
		MonomialExpr(std::string source);
		/// <summary>
		/// 计算表达式
		/// </summary>
		/// <returns>返回多项式</returns>
		Polyomial Eval() override;
		/// <summary>
		/// 带入自变量计算多项式
		/// </summary>
		/// <param name="x">自变量</param>
		/// <returns>多项式的值</returns>
		double Eval(double x) override;
		/// <summary>
		/// 计算表达式
		/// </summary>
		/// <param name="poly">多项式</param>
		/// <returns>返回多项式</returns>
		Polyomial Eval(Polyomial poly) override;
	};
}


