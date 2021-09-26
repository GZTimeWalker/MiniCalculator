#pragma once

#include <map>
#include <string>
#include <ostream>

#define IDMap std::map<int, long double>

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
        IDMap PFMap;
        /// <summary>
        /// 移除无用指数（系数为0）
        /// </summary>
        void Clean();
        /// <summary>
        /// 系数加法
        /// </summary>
        IDMap Add(IDMap left, IDMap right);
        /// <summary>
        /// 系数剪发
        /// </summary>
        IDMap Minus(IDMap left, IDMap right);

    public:
        Polyomial();
        Polyomial(const Polyomial& other);
        Polyomial(long double number);
        Polyomial(IDMap& data);

        /// <summary>
        /// 从多项式构造表达式语法树
        /// </summary>
        /// <returns>表达式语法树</returns>
        std::shared_ptr<Expr> AsExpr();
        /// <summary>
        /// 将多项式计算为数字（如果可能）
        /// </summary>
        /// <returns>数字</returns>
        long double AsNum();
        /// <summary>
        /// 多项式求导
        /// </summary>
        /// <returns></returns>
        Polyomial Derivative();

        Polyomial& operator+=(const Polyomial& other);
        Polyomial& operator-=(const Polyomial& other);
        Polyomial& operator*=(const Polyomial& other);
        Polyomial& operator*=(long double factor);
        Polyomial& operator^=(int exp);
        Polyomial& operator/=(long double divisor);
        Polyomial operator+(const Polyomial& other) const;
        Polyomial operator-(const Polyomial& other) const;
        Polyomial operator*(const Polyomial& other) const;
        Polyomial operator/(long double divisor) const;
        Polyomial operator^(int exp) const;
        Polyomial& operator-(void);

        friend std::ostream& operator<<(std::ostream& out, const Polyomial& polyomial);
    };
}