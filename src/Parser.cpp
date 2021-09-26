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
        // ax^b
        else if (Peek(TokenType::NUMBER, TokenType::X, TokenType::TIP, TokenType::NUMBER))
        {
            auto token = Match(TokenType::NUMBER);
            auto factor = std::stold(token.GetValue(Source));

            Match(TokenType::X);
            Match(TokenType::TIP);
            
            token = Match(TokenType::NUMBER);
            auto exp = std::stoi(token.GetValue(Source));

            return std::make_shared<MonomialExpr>(factor, exp);
        }
        // x^b
        else if (Peek(TokenType::X, TokenType::TIP, TokenType::NUMBER))
        {
            Match(TokenType::X);
            Match(TokenType::TIP);

            auto token = Match(TokenType::NUMBER);
            auto exp = std::stoi(token.GetValue(Source));

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
        auto ret = GetBaseExpr();
        while (Peek(TokenType::RSQUO))
        {
            Token _operator = Match();
            ret = std::make_shared<DerivativeExpr>(ret);
        }
        return ret;
    }

    std::shared_ptr<Expr> Parser::GetUnaryExpr()
    {
        Token op = Token(TokenType::NONE, 0, 0);
        bool after = true;

        if (Peek(TokenType::MINUS))
            op = Match(TokenType::MINUS);
        else if (Peek(TokenType::PLUS))
            op = Match(TokenType::PLUS);

        auto expr = GetDerivativeExpr();

        if (Peek(TokenType::RSQUO))
            op = Match(TokenType::RSQUO);

        if (op.Type == TokenType::NONE)
            return expr;
        
        return std::make_shared<UnaryExpr>(op, expr);
    }

    std::shared_ptr<Expr> Parser::GetPowExpr()
    {
        auto ret = GetUnaryExpr();
        while (Peek(TokenType::TIP))
        {
            Token _operator = Match();
            ret = std::make_shared<BinaryExpr>(ret, _operator, GetUnaryExpr());
        }
        return ret;
    }

    std::shared_ptr<Expr> Parser::GetMutiExpr()
    {
        auto ret = GetPowExpr();
        while (Peek(TokenType::STAR) || Peek(TokenType::SLASH) || Peek(TokenType::LEFT_PAREN))
        {
            if (Peek(TokenType::LEFT_PAREN))
            {
                Token _operator = Token(TokenType::STAR, 0, 0);
                ret = std::make_shared<BinaryExpr>(ret, _operator, GetPowExpr());
            }
            else
            {
                Token _operator = Match();
                ret = std::make_shared<BinaryExpr>(ret, _operator, GetPowExpr());
            }
        }
        return ret;
    }

    std::shared_ptr<Expr> Parser::GetPlusExpr()
    {
        auto ret = GetMutiExpr();
        while (Peek(TokenType::PLUS) || Peek(TokenType::MINUS))
        {
            Token _operator = Match();
            ret = std::make_shared<BinaryExpr>(ret, _operator, GetMutiExpr());
        }
        return ret;
    }

    Parser::Parser(const std::vector<Token>& tokens, std::string& source, std::map<std::string, std::shared_ptr<Expr>>* vars)
    {
        Begin = tokens.cbegin();
        End = tokens.cend();
        Current = tokens.cbegin();
        Source = source;
        Vars = vars;
    }

    std::shared_ptr<Expr> Parser::GenExpr()
    {
        return GetPlusExpr();
    }
}