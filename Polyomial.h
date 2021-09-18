#pragma once

#include <map>
#include <string>
#include <ostream>
#include "Expr.h"

namespace MiniCalculator
{
	class Polyomial
	{
	private:
		std::map<int, double> ExpFactorMap;
		void Clean();

	public:
		Polyomial();
		Polyomial(const Polyomial& other);
		Polyomial(std::map<int, double>& data);

		std::shared_ptr<Expr> AsExpr();
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