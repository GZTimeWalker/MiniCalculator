#include "Expr.h"
#include "Exception.h"
#include <cmath>

using namespace std;

namespace MiniCalculator
{
	Polyomial Expr::Eval()
	{
		return Polyomial();
	}

	Polyomial Expr::Eval(Polyomial poly)
	{
		return Polyomial();
	}

	double Expr::Eval(double x)
	{
		return 0.0;
	}

	Polyomial UnaryExpr::Eval()
	{
		Polyomial val = Right->Eval();

		switch (Operator.Type)
		{
		case TokenType::MINUS:
			return -val;
		default:
			throw SyntaxException(Operator.Start);
		}
	}

	double UnaryExpr::Eval(double x)
	{
		double val = Right->Eval(x);
		
		switch (Operator.Type)
		{
		case TokenType::MINUS:
			return -val;
		default:
			throw SyntaxException(Operator.Start);
		}
	}

	Polyomial UnaryExpr::Eval(Polyomial poly)
	{
		switch (Operator.Type)
		{
		case TokenType::MINUS:
			return -poly;
		default:
			throw SyntaxException(Operator.Start);
		}
	}

	MonomialExpr::MonomialExpr(std::string source)
	{
		auto x_pos = source.find('x');
		if (x_pos == std::string::npos)
			x_pos = source.find('X');

		if (x_pos == std::string::npos)
		{
			Exponent = 0;
			if (source.length() == 1 && source[0] == '.')
				throw UnexpectedNumberException(0);
			Factor = stod(source);
			return;
		}

		auto tip_pos = source.find('^');
		if (tip_pos == std::string::npos)
		{
			Exponent = 1;
			Factor = x_pos == 0 ? 1 : stod(source.substr(0, x_pos));
			return;
		}

		Factor = x_pos == 0 ? 1 : stod(source.substr(0, x_pos));
		Exponent = stoi(source.substr(tip_pos + 1, source.length() - tip_pos - 1));
	}

	Polyomial MonomialExpr::Eval()
	{
		map<int, double> expfactors;
		expfactors[Exponent] = Factor;
		return Polyomial(expfactors);
	}

	double MonomialExpr::Eval(double x)
	{
		return pow(x, Exponent) * Factor;
	}

	Polyomial MonomialExpr::Eval(Polyomial poly)
	{
		poly ^= Exponent;
		poly *= Factor;
		return poly;
	}

	Polyomial GroupingExpr::Eval()
	{
		return Expression->Eval();
	}

	double GroupingExpr::Eval(double x)
	{
		return Expression->Eval(x);
	}

	Polyomial GroupingExpr::Eval(Polyomial poly)
	{
		return Expression->Eval(poly);
	}

	Polyomial BinaryExpr::Eval()
	{
		Polyomial left = Left->Eval();
		Polyomial right = Right->Eval();

		switch (Operator.Type)
		{
		case TokenType::MINUS:
			return left - right;
		case TokenType::PLUS:
			return left + right;
		case TokenType::STAR:
			return left * right;
		default:
			throw SyntaxException(Operator.Start);
		}
	}

	double BinaryExpr::Eval(double x)
	{
		double left = Left->Eval(x);
		double right = Right->Eval(x);

		switch (Operator.Type)
		{
		case TokenType::MINUS:
			return left - right;
		case TokenType::PLUS:
			return left + right;
		case TokenType::STAR:
			return left * right;
		default:
			throw SyntaxException(Operator.Start);
		}
	}

	Polyomial BinaryExpr::Eval(Polyomial poly)
	{
		Polyomial left = Left->Eval(poly);
		Polyomial right = Right->Eval(poly);

		switch (Operator.Type)
		{
		case TokenType::MINUS:
			return left - right;
		case TokenType::PLUS:
			return left + right;
		case TokenType::STAR:
			return left * right;
		default:
			throw SyntaxException(Operator.Start);
		}
	}
}