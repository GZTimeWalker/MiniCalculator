#include "Expr.h"
#include "Exception.h"
#include <cmath>

using namespace std;

namespace MiniCalculator
{
    shared_ptr<Expr> Expr::Simplify()
    {
        return Eval().AsExpr();
    }

    Polyomial Expr::Eval()
    {
        return Polyomial();
    }

    Polyomial Expr::Eval(Polyomial poly)
    {
        return Polyomial();
    }

    long double Expr::Eval(long double x)
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

    long double UnaryExpr::Eval(long double x)
    {
        long double val = Right->Eval(x);

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

    MonomialExpr::MonomialExpr(long double factor, long double exponent)
    {
        long double exp = 0;
        if (modfl(exponent, &exp) > 0.0L)
            throw UnsupportedOperationException();

        Factor = factor;
        Exponent = (int)exp;
    }

    Polyomial MonomialExpr::Eval()
    {
        map<int, long double> expfactors;
        expfactors[Exponent] = Factor;
        return Polyomial(expfactors);
    }

    long double MonomialExpr::Eval(long double x)
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

    long double GroupingExpr::Eval(long double x)
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

        long double _right = 0.0L;

        switch (Operator.Type)
        {
        case TokenType::MINUS:
            return left - right;
        case TokenType::PLUS:
            return left + right;
        case TokenType::STAR:
            return left * right;
        case TokenType::SLASH:
            _right = right.AsNum();
            return left / _right;
        case TokenType::TIP:
            if (modfl(right.AsNum(), &_right) > 0.0L)
                throw UnsupportedOperationException();
            return left ^ (int)_right;
        default:
            throw SyntaxException(Operator.Start);
        }
    }

    long double BinaryExpr::Eval(long double x)
    {
        long double left = Left->Eval(x);
        long double right = Right->Eval(x);

        switch (Operator.Type)
        {
        case TokenType::MINUS:
            return left - right;
        case TokenType::PLUS:
            return left + right;
        case TokenType::STAR:
            return left * right;
        case TokenType::SLASH:
            return left / right;
        case TokenType::TIP:
            return std::powl(left, right);
        default:
            throw SyntaxException(Operator.Start);
        }
    }

    Polyomial BinaryExpr::Eval(Polyomial poly)
    {
        Polyomial left = Left->Eval(poly);
        Polyomial right = Right->Eval(poly);

        long double _right = 0.0L;

        switch (Operator.Type)
        {
        case TokenType::MINUS:
            return left - right;
        case TokenType::PLUS:
            return left + right;
        case TokenType::STAR:
            return left * right;
        case TokenType::SLASH:
            _right = right.AsNum();
            return left / _right;
        case TokenType::TIP:
            if (modfl(right.AsNum(), &_right) > 0.0L)
                throw UnsupportedOperationException();
            return left ^ (int)_right;
        default:
            throw SyntaxException(Operator.Start);
        }
    }

    Polyomial CompoundExpr::Eval()
    {
        return Base->Eval(Compound->Eval());
    }

    long double CompoundExpr::Eval(long double x)
    {
        return Base->Eval(Compound->Eval(x));
    }

    Polyomial CompoundExpr::Eval(Polyomial poly)
    {
        return Base->Eval(Compound->Eval(poly));
    }

    Polyomial NumberExpr::Eval()
    {
        return Polyomial(Number);
    }

    long double NumberExpr::Eval(long double x)
    {
        return Number;
    }

    Polyomial NumberExpr::Eval(Polyomial poly)
    {
        return Polyomial(Number);
    }

    Polyomial DerivativeExpr::Eval()
    {
        return Expression->Eval().Derivative();
    }

    long double DerivativeExpr::Eval(long double x)
    {
        return Expression->Eval().Derivative().AsExpr()->Eval(x);
    }

    Polyomial DerivativeExpr::Eval(Polyomial poly)
    {
        return Expression->Eval().Derivative().AsExpr()->Eval(poly);
    }
}