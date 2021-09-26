#pragma once

#include <map>
#include <string>
#include <ostream>

#define IDMap std::map<int, long double>

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
        IDMap PFMap;
        /// <summary>
        /// �Ƴ�����ָ����ϵ��Ϊ0��
        /// </summary>
        void Clean();
        /// <summary>
        /// ϵ���ӷ�
        /// </summary>
        IDMap Add(IDMap left, IDMap right);
        /// <summary>
        /// ϵ������
        /// </summary>
        IDMap Minus(IDMap left, IDMap right);

    public:
        Polyomial();
        Polyomial(const Polyomial& other);
        Polyomial(long double number);
        Polyomial(IDMap& data);

        /// <summary>
        /// �Ӷ���ʽ������ʽ�﷨��
        /// </summary>
        /// <returns>���ʽ�﷨��</returns>
        std::shared_ptr<Expr> AsExpr();
        /// <summary>
        /// ������ʽ����Ϊ���֣�������ܣ�
        /// </summary>
        /// <returns>����</returns>
        long double AsNum();
        /// <summary>
        /// ����ʽ��
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