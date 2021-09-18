#include "Polyomial.h"
#include "Expr.h"
#include <iomanip>
#include <vector>

using namespace std;

namespace MiniCalculator {
	void Polyomial::Clean()
	{
		auto iter = ExpFactorMap.begin();
		vector<int> delete_list;

		while (iter != ExpFactorMap.end())
		{
			if ((*iter).second == 0.0)
				delete_list.push_back((*iter).first);
			++iter;
		}

		for (auto i : delete_list)
			ExpFactorMap.erase(i);
	}

	Polyomial::Polyomial()
	{
	}

	Polyomial::Polyomial(const Polyomial& other)
	{
		ExpFactorMap = other.ExpFactorMap;
	}

	Polyomial::Polyomial(map<int, double>& data)
	{
		ExpFactorMap = data;
	}

	shared_ptr<Expr> Polyomial::AsExpr()
	{
		auto cur = ExpFactorMap.begin();
		shared_ptr<Expr> expr = make_shared<MonomialExpr>((*cur).second, (*cur).first);

		while (++cur != ExpFactorMap.end())
		{
			auto rhs = make_shared<MonomialExpr>((*cur).second, (*cur).first);
			expr = make_shared<BinaryExpr>(expr, Token(TokenType::PLUS, 0, 0), rhs);
		}

		return expr;
	}

	Polyomial Polyomial::Derivative()
	{
		Polyomial result;

		for (auto& item : ExpFactorMap)
			if(item.first != 0)
				result.ExpFactorMap[item.first - 1] = item.second * item.first;

		Clean();
		return result;
	}

	Polyomial& Polyomial::operator+=(const Polyomial& other)
	{
		for (auto& item : other.ExpFactorMap)
			ExpFactorMap[item.first] += item.second;
		Clean();
		return *this;
	}

	Polyomial& Polyomial::operator-=(const Polyomial& other)
	{
		for (auto& item : other.ExpFactorMap)
			ExpFactorMap[item.first] -= item.second;
		Clean();
		return *this;
	}

	Polyomial& Polyomial::operator*=(const Polyomial& other)
	{
		this->ExpFactorMap = ((*this) * other).ExpFactorMap;
		return *this;
	}

	Polyomial& Polyomial::operator*=(double factor)
	{
		if (factor == 1)
			return *this;

		for (auto& item : ExpFactorMap)
			item.second *= factor;
		return *this;
	}

	Polyomial& Polyomial::operator^=(int exp)
	{
		if (exp == 1)
			return *this;

		if (exp == 0)
		{
			ExpFactorMap.clear();
			ExpFactorMap[0] = 1;
			return *this;
		}

		Polyomial poly = *this;

		for (int i = 1; i < exp; ++i)
			*this *= poly;

		return *this;
	}

	Polyomial Polyomial::operator+(const Polyomial& other) const
	{
		Polyomial result(*this);
	
		for (auto& item : other.ExpFactorMap)
			result.ExpFactorMap[item.first] += item.second;

		result.Clean();
		return result;
	}

	Polyomial Polyomial::operator-(const Polyomial& other) const
	{
		Polyomial result(*this);

		for (auto& item : other.ExpFactorMap)
			result.ExpFactorMap[item.first] -= item.second;

		result.Clean();
		return result;
	}

	Polyomial Polyomial::operator*(const Polyomial& other) const
	{
		Polyomial result;
		Polyomial part;

		for (auto& factor : ExpFactorMap)
		{
			for (auto& item : other.ExpFactorMap)
				part.ExpFactorMap[item.first + factor.first] = item.second * factor.second;

			result += part;
			part.ExpFactorMap.clear();
		}

		result.Clean();
		return result;
	}

	Polyomial& Polyomial::operator-(void)
	{
		for (auto &pair : ExpFactorMap)
			pair.second = -pair.second;
		Clean();
		return *this;
	}

    std::ostream& operator<<(std::ostream& out, const Polyomial& polyomial)
	{
		out << setiosflags(ios::fixed) << setprecision(2);
		double factor;

		if (polyomial.ExpFactorMap.size() == 0)
		{
			out << 0.0;
			return out;
		}

		for (auto iter = polyomial.ExpFactorMap.begin(); iter != polyomial.ExpFactorMap.end(); ++iter)
		{
			factor = (*iter).second;

			if (iter == polyomial.ExpFactorMap.begin())
			{
				if(factor < 0)
					out << "- ";
			}
			else
				out << (factor > 0 ? " + " : " - ");

			factor = factor > 0 ? factor : -factor;

			if (factor != 1 || (*iter).first == 0)
				out << factor;

			if ((*iter).first == 0)
				continue;
			else if ((*iter).first == 1)
				out << "x";
			else
				out << "x^" << (*iter).first;
		}

		return out;
	}
}

