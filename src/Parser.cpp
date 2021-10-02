#include "Parser.h"
#include "Expr.h"
#include "Exception.h"
#include "Utils.h"

#include <memory>

namespace MiniCalculator
{
    Token Parser::Match()
    {
        if (Current >= End)
            throw UnexpectedEOFException();

        return *(Current++);
    }

    Token Parser::Match(TokenType type)
    {
        if (Current >= End)
            throw UnexpectedEOFException();

        auto& token = *Current;
        if (token.Type != type)
            throw UnexpectedTokenException(token.Start);

        ++Current;
        return token;
    }

    bool Parser::Peek(TokenType type)
    {
        if (Current == End)
            return false;
        return (*Current).Type == type;
    }

    bool Parser::Peek(TokenType type, TokenType next)
    {
        for(int i = 0; i < 2; ++i)
            if ((Current + i) == End)
                return false;
        return (*Current).Type == type && (*(Current + 1)).Type == next;
    }

    bool Parser::Peek(TokenType type, TokenType next, TokenType _next)
    {
        for (int i = 0; i < 3; ++i)
            if ((Current + i) == End)
                return false;
        return (*Current).Type == type && (*(Current + 1)).Type == next && (*(Current + 2)).Type == _next;
    }

    bool Parser::Peek(TokenType type, TokenType next, TokenType _next, TokenType __next)
    {
        for (int i = 0; i < 4; ++i)
            if ((Current + i) == End)
                return false;
        return (*Current).Type == type && (*(Current + 1)).Type == next && (*(Current + 2)).Type == _next  && (*(Current + 3)).Type == __next;
    }

    std::shared_ptr<Expr> Parser::GetBaseExpr()
    {
        // ( Expr )
        if (Peek(TokenType::LEFT_PAREN))
        {
            Match(TokenType::LEFT_PAREN);
            auto expr = GetPlusExpr();
            Match(TokenType::RIGHT_PAREN);
            return std::make_shared<GroupingExpr>(expr);
        }
        // ax^( Expr )
        else if (Peek(TokenType::NUMBER, TokenType::X, TokenType::TIP, TokenType::LEFT_PAREN))
        {
            auto token = Match(TokenType::NUMBER);
            auto factor = std::stold(token.GetValue(Source));

            Match(TokenType::X);
            Match(TokenType::TIP);

            Match(TokenType::LEFT_PAREN);
            auto expr = GetPlusExpr();
            Match(TokenType::RIGHT_PAREN);

            auto exp = expr->Eval().AsNum();

            return std::make_shared<MonomialExpr>(factor, exp);
        }
        // ax^b
        else if (Peek(TokenType::NUMBER, TokenType::X, TokenType::TIP, TokenType::NUMBER))
        {
            auto token = Match(TokenType::NUMBER);
            auto factor = std::stold(token.GetValue(Source));

            Match(TokenType::X);
            Match(TokenType::TIP);
            
            token = Match(TokenType::NUMBER);
            auto exp = std::stold(token.GetValue(Source));

            return std::make_shared<MonomialExpr>(factor, exp);
        }
        // x^( Expr )
        else if (Peek(TokenType::X, TokenType::TIP, TokenType::LEFT_PAREN))
        {
            Match(TokenType::X);
            Match(TokenType::TIP);

            Match(TokenType::LEFT_PAREN);
            auto expr = GetPlusExpr();
            Match(TokenType::RIGHT_PAREN);

            auto exp = expr->Eval().AsNum();

            return std::make_shared<MonomialExpr>(1.0L, exp);
        }
        // x^b
        else if (Peek(TokenType::X, TokenType::TIP, TokenType::NUMBER))
        {
            Match(TokenType::X);
            Match(TokenType::TIP);

            auto token = Match(TokenType::NUMBER);
            auto exp = std::stold(token.GetValue(Source));

            return std::make_shared<MonomialExpr>(1.0L, exp);
        }
        // ax
        else if (Peek(TokenType::NUMBER, TokenType::X))
        {
            auto token = Match(TokenType::NUMBER);
            auto factor = std::stold(token.GetValue(Source));

            Match(TokenType::X);

            return std::make_shared<MonomialExpr>(factor, 1);
        }
        // x
        else if (Peek(TokenType::X))
        {
            Match(TokenType::X);
            return std::make_shared<MonomialExpr>(1.0L , 1);
        }
        // Number
        else if (Peek(TokenType::NUMBER))
        {
            auto token = Match(TokenType::NUMBER);
            auto number = std::stold(token.GetValue(Source));
            return std::make_shared<NumberExpr>(number);
        }
        // Var ( Expr )
        else if (Peek(TokenType::VAR, TokenType::LEFT_PAREN))
        {
            auto token = Match(TokenType::VAR);
            auto iter = Vars->find(token.GetValue(Source));

            if (iter == Vars->end())
                throw UnexpectedExpressionException(token.Start);

            Match(TokenType::LEFT_PAREN);
            auto expr = GetPlusExpr();
            Match(TokenType::RIGHT_PAREN);

            return std::make_shared<CompoundExpr>((*iter).second, expr);
        }
        // Var
        else if (Peek(TokenType::VAR))
        {
            auto token = Match(TokenType::VAR);
            auto iter = Vars->find(token.GetValue(Source));

            if(iter == Vars->end())
                throw UnexpectedExpressionException(token.Start);

            return Vars->at(token.GetValue(Source));
        }
        if (Current == End)
            throw UnexpectedEOFException();
        throw UnexpectedExpressionException((*Current).Start);
    }

    std::shared_ptr<Expr> Parser::GetDerivativeExpr()
    {
        if (Utils::DEBUG)
        {
            Utils::PrintDebugLine(true, "Derivative Expr");
            Utils::PrintDebugLine(true, "Base Expr");
        }
        auto ret = GetBaseExpr();
        if (Utils::DEBUG)
        {
            Utils::PrintDebugExpr(ret->Eval());
            Utils::PrintDebugLine(false, "Base Expr");
        }
        while (Peek(TokenType::RSQUO))
        {
            Token _operator = Match();
            if (Utils::DEBUG)
                Utils::PrintDebugExprWithToken(ret->Eval(), _operator.Type);
            ret = std::make_shared<DerivativeExpr>(ret);
        }
        if (Utils::DEBUG)
            Utils::PrintDebugLine(false, "Derivative Expr");
        return ret;
    }

    std::shared_ptr<Expr> Parser::GetUnaryExpr()
    {
        if (Utils::DEBUG)
            Utils::PrintDebugLine(true, "Unary Expr");
        Token _operator = Token(TokenType::NONE, 0, 0);

        if (Peek(TokenType::MINUS))
            _operator = Match(TokenType::MINUS);
        else if (Peek(TokenType::PLUS))
            _operator = Match(TokenType::PLUS);

        auto expr = GetDerivativeExpr();



        if (_operator.Type == TokenType::NONE)
        {
            if (Utils::DEBUG)
                Utils::PrintDebugLine(false, "Unary Expr");
            return expr;
        }
        
        if (Utils::DEBUG)
        {
            Utils::PrintDebugExprWithToken(expr->Eval(), _operator.Type); 
            Utils::PrintDebugLine(false, "Unary Expr");
        }

        return std::make_shared<UnaryExpr>(_operator, expr);
    }

    std::shared_ptr<Expr> Parser::GetPowExpr()
    {
        if (Utils::DEBUG)
            Utils::PrintDebugLine(true, "Pow Expr");
        auto ret = GetUnaryExpr();
        while (Peek(TokenType::TIP))
        {
            Token _operator = Match();
            if (Utils::DEBUG)
                Utils::PrintDebugExprWithToken(ret->Eval(), _operator.Type);
            ret = std::make_shared<BinaryExpr>(ret, _operator, GetUnaryExpr());
        }
        if (Utils::DEBUG)
            Utils::PrintDebugLine(false, "Pow Expr");
        return ret;
    }

    std::shared_ptr<Expr> Parser::GetMutiExpr()
    {
        if (Utils::DEBUG)
            Utils::PrintDebugLine(true, "Muti Expr");
        auto ret = GetPowExpr();
        while (Peek(TokenType::STAR) || Peek(TokenType::SLASH) || Peek(TokenType::LEFT_PAREN))
        {
            if (Peek(TokenType::LEFT_PAREN))
            {
                Token _operator = Token(TokenType::STAR, 0, 0);
                if (Utils::DEBUG)
                    Utils::PrintDebugExprWithToken(ret->Eval(), _operator.Type);
                ret = std::make_shared<BinaryExpr>(ret, _operator, GetPowExpr());
            }
            else
            {
                Token _operator = Match();
                if (Utils::DEBUG)
                    Utils::PrintDebugExprWithToken(ret->Eval(), _operator.Type);
                ret = std::make_shared<BinaryExpr>(ret, _operator, GetPowExpr());
            }
        }
        if (Utils::DEBUG)
            Utils::PrintDebugLine(false, "Muti Expr");
        return ret;
    }

    std::shared_ptr<Expr> Parser::GetPlusExpr()
    {
        if (Utils::DEBUG)
            Utils::PrintDebugLine(true, "Plus Expr");
        auto ret = GetMutiExpr();
        while (Peek(TokenType::PLUS) || Peek(TokenType::MINUS))
        {
            Token _operator = Match();
            if (Utils::DEBUG)
                Utils::PrintDebugExprWithToken(ret->Eval(), _operator.Type);
            ret = std::make_shared<BinaryExpr>(ret, _operator, GetMutiExpr());
        }
        if (Utils::DEBUG)
            Utils::PrintDebugLine(false, "Plus Expr");
        return ret;
    }

    Parser::Parser(const std::vector<Token>& tokens, std::string& source, std::map<std::string, std::shared_ptr<Expr>>* vars)
    {
        End = tokens.cend();
        Current = tokens.cbegin();
        Source = source;
        Vars = vars;
    }

    std::shared_ptr<Expr> Parser::GenExpr()
    {
        auto expr = GetPlusExpr();
        if (Current != End)
        {
            auto token = Match();
            throw UnexpectedTokenException(token.Start);
        }
        return expr;
    }
}