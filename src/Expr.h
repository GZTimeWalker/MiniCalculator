#pragma once

#include <memory>
#include "Polyomial.h"
#include "Token.h"

namespace MiniCalculator
{
    /// <summary>
    /// ���ʽ�Ļ���
    /// </summary>
    class Expr
    {
    public:
        /// <summary>
        /// ������ʽ
        /// </summary>
        std::shared_ptr<Expr> Simplify();

        /// <summary>
        /// ������ʽ
        /// </summary>
        /// <returns>���ض���ʽ</returns>
        virtual Polyomial Eval();

        /// <summary>
        /// ������ʽ
        /// </summary>
        /// <param name="poly">����ʽ</param>
        /// <returns>���ض���ʽ</returns>
        virtual Polyomial Eval(Polyomial poly);

        /// <summary>
        /// �����Ա����������ʽ
        /// </summary>
        /// <param name="x">�Ա���</param>
        /// <returns>����ʽ��ֵ</returns>
        virtual long double Eval(long double x);
    };

    /// <summary>
    /// ��Ԫ���ʽ
    /// </summary>
    class BinaryExpr : public Expr
    {
    private:
        /// <summary>
        /// ����ʽ
        /// </summary>
        std::shared_ptr<Expr> Left;
        /// <summary>
        /// ��Ԫ�����
        /// </summary>
        Token Operator;
        /// <summary>
        /// �ұ��ʽ
        /// </summary>
        std::shared_ptr<Expr> Right;

    public:
        BinaryExpr(std::shared_ptr<Expr> left, Token _operator, std::shared_ptr<Expr> right) : Left(left), Operator(_operator), Right(right) {}
        /// <summary>
        /// ������ʽ
        /// </summary>
        /// <returns>���ض���ʽ</returns>
        Polyomial Eval() override;
        /// <summary>
        /// �����Ա����������ʽ
        /// </summary>
        /// <param name="x">�Ա���</param>
        /// <returns>����ʽ��ֵ</returns>
        long double Eval(long double x) override;
        /// <summary>
        /// ������ʽ
        /// </summary>
        /// <param name="poly">����ʽ</param>
        /// <returns>���ض���ʽ</returns>
        Polyomial Eval(Polyomial poly) override;
    };

    /// <summary>
    /// ������ʽ
    /// </summary>
    class GroupingExpr : public Expr
    {
    private:
        /// <summary>
        /// ���ʽ
        /// </summary>
        std::shared_ptr<Expr> Expression;

    public:
        GroupingExpr(std::shared_ptr<Expr> expression): Expression(expression) {}
        /// <summary>
        /// ������ʽ
        /// </summary>
        /// <returns>���ض���ʽ</returns>
        Polyomial Eval() override;
        /// <summary>
        /// �����Ա����������ʽ
        /// </summary>
        /// <param name="x">�Ա���</param>
        /// <returns>����ʽ��ֵ</returns>
        long double Eval(long double x) override;
        /// <summary>
        /// ������ʽ
        /// </summary>
        /// <param name="poly">����ʽ</param>
        /// <returns>���ض���ʽ</returns>
        Polyomial Eval(Polyomial poly) override;
    };

    /// <summary>
    /// ���ϱ��ʽ
    /// </summary>
    class CompoundExpr : public Expr
    {
    private:
        /// <summary>
        /// �����ʽ
        /// </summary>
        std::shared_ptr<Expr> Base;

        /// <summary>
        /// �����ϱ��ʽ
        /// </summary>
        std::shared_ptr<Expr> Compound;

    public:
        CompoundExpr(std::shared_ptr<Expr> base, std::shared_ptr<Expr> compound) : Base(base), Compound(compound) {}
        /// <summary>
        /// ������ʽ
        /// </summary>
        /// <returns>���ض���ʽ</returns>
        Polyomial Eval() override;
        /// <summary>
        /// �����Ա����������ʽ
        /// </summary>
        /// <param name="x">�Ա���</param>
        /// <returns>����ʽ��ֵ</returns>
        long double Eval(long double x) override;
        /// <summary>
        /// ������ʽ
        /// </summary>
        /// <param name="poly">����ʽ</param>
        /// <returns>���ض���ʽ</returns>
        Polyomial Eval(Polyomial poly) override;
    };

    /// <summary>
    /// һԪ���ʽ
    /// </summary>
    class UnaryExpr : public Expr
    {
    private:
        /// <summary>
        /// һԪ�����
        /// </summary>
        Token Operator;
        /// <summary>
        /// �ұ��ʽ
        /// </summary>
        std::shared_ptr<Expr> Right;
    public:
        UnaryExpr(Token _operator, std::shared_ptr<Expr> right): Operator(_operator), Right(right){}
        /// <summary>
        /// ������ʽ
        /// </summary>
        /// <returns>���ض���ʽ</returns>
        Polyomial Eval() override;
        /// <summary>
        /// �����Ա����������ʽ
        /// </summary>
        /// <param name="x">�Ա���</param>
        /// <returns>����ʽ��ֵ</returns>
        long double Eval(long double x) override;
        /// <summary>
        /// ������ʽ
        /// </summary>
        /// <param name="poly">����ʽ</param>
        /// <returns>���ض���ʽ</returns>
        Polyomial Eval(Polyomial poly) override;
    };

    /// <summary>
    /// ����ʽ���ʽ
    /// </summary>
    class MonomialExpr : public Expr
    {
    private:
        /// <summary>
        /// ϵ��
        /// </summary>
        long double Factor;
        /// <summary>
        /// ָ��
        /// </summary>
        int Exponent;
    public:
        MonomialExpr(long double factor, int exponent) : Factor(factor), Exponent(exponent) {}
        MonomialExpr(long double factor, long double exponent);
        /// <summary>
        /// ������ʽ
        /// </summary>
        /// <returns>���ض���ʽ</returns>
        Polyomial Eval() override;
        /// <summary>
        /// �����Ա����������ʽ
        /// </summary>
        /// <param name="x">�Ա���</param>
        /// <returns>����ʽ��ֵ</returns>
        long double Eval(long double x) override;
        /// <summary>
        /// ������ʽ
        /// </summary>
        /// <param name="poly">����ʽ</param>
        /// <returns>���ض���ʽ</returns>
        Polyomial Eval(Polyomial poly) override;
    };

    /// <summary>
    /// ���ֱ��ʽ
    /// </summary>
    class NumberExpr : public Expr
    {
    private:
        /// <summary>
        /// ����
        /// </summary>
        long double Number;
    public:
        NumberExpr(long double number) : Number(number) {}
        /// <summary>
        /// ������ʽ
        /// </summary>
        /// <returns>���ض���ʽ</returns>
        Polyomial Eval() override;
        /// <summary>
        /// �����Ա����������ʽ
        /// </summary>
        /// <param name="x">�Ա���</param>
        /// <returns>����ʽ��ֵ</returns>
        long double Eval(long double x) override;
        /// <summary>
        /// ������ʽ
        /// </summary>
        /// <param name="poly">����ʽ</param>
        /// <returns>���ض���ʽ</returns>
        Polyomial Eval(Polyomial poly) override;
    };

    /// <summary>
    /// �󵼱��ʽ
    /// </summary>
    class DerivativeExpr : public Expr
    {
    private:
        /// <summary>
        /// ���ʽ
        /// </summary>
        std::shared_ptr<Expr> Expression;
    public:
        DerivativeExpr(std::shared_ptr<Expr> expr) : Expression(expr) {}
        /// <summary>
        /// ������ʽ
        /// </summary>
        /// <returns>���ض���ʽ</returns>
        Polyomial Eval() override;
        /// <summary>
        /// �����Ա����������ʽ
        /// </summary>
        /// <param name="x">�Ա���</param>
        /// <returns>����ʽ��ֵ</returns>
        long double Eval(long double x) override;
        /// <summary>
        /// ������ʽ
        /// </summary>
        /// <param name="poly">����ʽ</param>
        /// <returns>���ض���ʽ</returns>
        Polyomial Eval(Polyomial poly) override;
    };
}


