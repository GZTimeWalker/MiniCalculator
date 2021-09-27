#include "Polyomial.h"
#include "Expr.h"
#include <iomanip>
#include <vector>

using namespace std;

namespace MiniCalculator {
    void Polyomial::Clean()
    {
        auto iter = PFMap.begin();
        vector<int> delete_list;

        while (iter != PFMap.end())
        {
            if ((*iter).second == 0.0)
                delete_list.push_back((*iter).first);
            ++iter;
        }

        for (auto i : delete_list)
            PFMap.erase(i);
    }

    IDMap Polyomial::Add(IDMap left, IDMap right)
    {
        return IDMap();
    }

    IDMap Polyomial::Minus(IDMap left, IDMap right)
    {
        return IDMap();
    }

    Polyomial::Polyomial()
    {
    }

    Polyomial::Polyomial(const Polyomial& other)
    {
        PFMap = other.PFMap;
    }

    Polyomial::Polyomial(long double number)
    {
        PFMap[0] = number;
    }

    Polyomial::Polyomial(IDMap& data)
    {
        PFMap = data;
    }

    shared_ptr<Expr> Polyomial::AsExpr()
    {
        auto cur = PFMap.begin();
        shared_ptr<Expr> expr = make_shared<MonomialExpr>((*cur).second, (*cur).first);

        while (++cur != PFMap.end())
        {
            auto rhs = make_shared<MonomialExpr>((*cur).second, (*cur).first);
            expr = make_shared<BinaryExpr>(expr, Token(TokenType::PLUS, 0, 0), rhs);
        }

        return expr;
    }

    long double Polyomial::AsNum()
    {
        if (PFMap.size() != 1 || (*(PFMap.begin())).first != 0)
            throw UnsupportedOperationException(-2);

        return PFMap[0];
    }

    Polyomial Polyomial::Derivative()
    {
        Polyomial result;
        
        if (PFMap.size() == 1 && (*(PFMap.begin())).first == 0)
            return Polyomial(0);

        for (auto& item : PFMap)
            if(item.first != 0)
                result.PFMap[item.first - 1] = item.second * item.first;

        result.Clean();
        return result;
    }

    Polyomial& Polyomial::operator+=(const Polyomial& other)
    {
        for (auto& item : other.PFMap)
            PFMap[item.first] += item.second;
        Clean();
        return *this;
    }

    Polyomial& Polyomial::operator-=(const Polyomial& other)
    {
        for (auto& item : other.PFMap)
            PFMap[item.first] -= item.second;
        Clean();
        return *this;
    }

    Polyomial& Polyomial::operator*=(const Polyomial& other)
    {
        auto res = (*this) * other;
        this->PFMap = res.PFMap;
        return *this;
    }

    Polyomial& Polyomial::operator*=(long double factor)
    {
        if (factor == 1)
            return *this;

        for (auto& item : PFMap)
            item.second *= factor;
        return *this;
    }

    Polyomial& Polyomial::operator^=(int exp)
    {
        if (exp == 1)
            return *this;

        if (exp == 0)
        {
            PFMap.clear();
            PFMap[0] = 1.00L;
            return *this;
        }

        Polyomial poly = *this;

        --exp;

        while (exp > 0)
        {
            if ((exp & 1) == 1)
                *this *= poly;
            poly *= poly;
            exp >>= 1;
        }

        return *this;
    }

    Polyomial Polyomial::operator+(const Polyomial& other) const
    {
        Polyomial result(*this);
    
        for (auto& item : other.PFMap)
            result.PFMap[item.first] += item.second;

        result.Clean();
        return result;
    }

    Polyomial Polyomial::operator-(const Polyomial& other) const
    {
        Polyomial result(*this);

        for (auto& item : other.PFMap)
            result.PFMap[item.first] -= item.second;

        result.Clean();
        return result;
    }

    Polyomial Polyomial::operator*(const Polyomial& other) const
    {
        if (PFMap.size() == 1 && (*(PFMap.begin())).first == 0 && (*(PFMap.begin())).second == 0)
            return Polyomial(0);

        if (other.PFMap.size() == 1 && (*(other.PFMap.begin())).first == 0 && (*(other.PFMap.begin())).second == 0)
            return Polyomial(0);

        Polyomial result;
        Polyomial part;

        for (auto& factor : PFMap)
        {
            for (auto& item : other.PFMap)
                part.PFMap[item.first + factor.first] = item.second * factor.second;

            result += part;
            part.PFMap.clear();
        }

        result.Clean();
        return result;
    }

    Polyomial Polyomial::operator/(long double divisor) const
    {
        Polyomial result(*this);
        result /= divisor;
        return result;
    }

    Polyomial& Polyomial::operator/=(long double divisor)
    {
        if (divisor == 1)
            return *this;

        for (auto& item : PFMap)
            item.second /= divisor;
        return *this;
    }

    Polyomial Polyomial::operator^(int exp) const
    {
        Polyomial result(*this);
        result ^= exp;
        return result;
    }

    Polyomial& Polyomial::operator-(void)
    {
        for (auto &pair : PFMap)
            pair.second = -pair.second;
        Clean();
        return *this;
    }

    std::ostream& operator<<(std::ostream& out, const Polyomial& polyomial)
    {
        out << setiosflags(ios::fixed) << setprecision(2);
        long double factor;

        if (polyomial.PFMap.size() == 0)
        {
            out << 0.0;
            return out;
        }

        for (auto iter = polyomial.PFMap.begin(); iter != polyomial.PFMap.end(); ++iter)
        {
            factor = (*iter).second;

            if (iter == polyomial.PFMap.begin())
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
            {
                if ((*iter).first > 0)
                    out << "x^" << (*iter).first;
                else
                    out << "x^(" << (*iter).first << ")";
            }
        }

        return out;
    }
}

