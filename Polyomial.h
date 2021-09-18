#pragma once

#include <map>
#include <string>
#include <ostream>


namespace MiniCalculator
{
	class Expr;
	/// <summary>
	/// 多项式
	/// </summary>
	class Polyomial
	{
	private:
		/// <summary>
		/// 指数和系数的映射
		/// </summary>
		std::map<int, double> ExpFactorMap;
		/// <summary>
		/// 移除无用指数（系数为0）
		/// </summary>
		void Clean();

	public:
		Polyomial();
		Polyomial(const Polyomial& other);
		Polyomial(std::map<int, double>& data);

		/// <summary>
		/// 从多项式构造表达式语法树
		/// </summary>
		/// <returns>表达式语法树</returns>
		std::shared_ptr<Expr> AsExpr();
		/// <summary>
		/// 多项式求导
		/// </summary>
		/// <returns></returns>
		Polyomial Derivative();

		Polyomial& operator+=(const Polyomial& other);
		Polyomial& operator-=(const Polyomial& other);
		Polyomial& operator*=(const Polyomial& other);
		Polyomial& operator*=(double factor);
		Polyomial& operator^=(int exp);
		Polyomial operator+(const Polyomial& other) const;
		Polyomial operator-(const Polyomial& other) const;
		Polyomial operator*(const Polyomial& other) const;
		Polyomial& operator-(void);

		friend std::ostream& operator<<(std::ostream& out, const Polyomial& polyomial);
	};
}