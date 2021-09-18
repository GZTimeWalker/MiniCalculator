#include "Parser.h"
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
        if (Current >= End)
            return false;
        return (*Current).Type == type;
    }

    std::shared_ptr<Expr> Parser::GetBaseExpr()
    {
        if (Peek(TokenType::LEFT_PAREN))
        {
            Match(TokenType::LEFT_PAREN);
            auto expr = GetPlusExpr();
            Match(TokenType::RIGHT_PAREN);
            return std::make_shared<GroupingExpr>(expr);
        }
        else if (Peek(TokenType::MONOMIAL))
        {
            auto token = Match(TokenType::MONOMIAL);
            try
            {
                return std::make_shared<MonomialExpr>(token.GetValue(Source));
            }
            catch (...)
            {
                throw UnexpectedNumberException(token.Start);
            }
        }
        else if (Peek(TokenType::VAR))
        {
            auto token = Match(TokenType::VAR);
            auto iter = Vars->find(token.GetValue(Source));

            if(iter == Vars->end())
                throw UnexpectedExpressionException((*Current).Start);

            return Vars->at(token.GetValue(Source));
        }
        if (Current == End)
            throw UnexpectedEOFException();
        throw UnexpectedExpressionException((*Current).Start);
    }

    std::shared_ptr<Expr> Parser::GetUnaryExpr()
    {
        Token op = Token(TokenType::NONE, 0, 0);

        if (Peek(TokenType::MINUS))
            op = Match(TokenType::MINUS);
        else if (Peek(TokenType::PLUS))
            op = Match(TokenType::PLUS);

        auto expr = GetBaseExpr();

        if (op.Type == TokenType::NONE)
            return expr;
        
        return std::make_shared<UnaryExpr>(op, expr);
    }

    std::shared_ptr<Expr> Parser::GetMutiExpr()
    {
        auto ret = GetUnaryExpr();
        while (Peek(TokenType::STAR) || Peek(TokenType::LEFT_PAREN))
        {
            if (Peek(TokenType::STAR))
            {
                Token _operator = Match();
                ret = std::make_shared<BinaryExpr>(ret, _operator, GetUnaryExpr());
            }
            else
            {
                Token _operator = Token(TokenType::STAR, 0, 0);
                ret = std::make_shared<BinaryExpr>(ret, _operator, GetUnaryExpr());
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