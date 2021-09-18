#pragma once

#include <map>
#include <string>
#include <ostream>


namespace MiniCalculator
{
	class Expr;
	/// <summary>
	/// ����ʽ
	/// </summary>
	class Polyomial
	{
	private:
		/// <summary>
		/// ָ����ϵ����ӳ��
		/// </summary>
		std::map<int, double> ExpFactorMap;
		/// <summary>
		/// �Ƴ�����ָ����ϵ��Ϊ0��
		/// </summary>
		void Clean();

	public:
		Polyomial();
		Polyomial(const Polyomial& other);
		Polyomial(std::map<int, double>& data);

		/// <summary>
		/// �Ӷ���ʽ������ʽ�﷨��
		/// </summary>
		/// <returns>���ʽ�﷨��</returns>
		std::shared_ptr<Expr> AsExpr();
		/// <summary>
		/// ����ʽ��
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