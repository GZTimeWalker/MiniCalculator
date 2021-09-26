#include <iostream>
#include <string>
#include <map>

#include "Parser.h"
#include "Expr.h"
#include "Lexer.h"
// #include "Test.cpp"

using namespace MiniCalculator;
using namespace std;

int main()
{
    Utils::Init();

    auto vars = new std::map<std::string, std::shared_ptr<Expr>>();

    string input;
    string flag, content, param;
    size_t equal_pos = -1;
    long double x;
    
    // main loop
    while (true)
    {
        Utils::Print(" > ", Color::YELLOW);

        Utils::SetColor(Color::WHITE);

        getline(cin, input);

        if (input == "help")
        {
            Utils::PrintHelp();
            continue;
        }

        if (input == "exit")
            break;

        // 赋值语句
        equal_pos = input.find('=');
        if (equal_pos != input.npos)
        {
            flag = input.substr(0, equal_pos);

            // Trim
            flag.erase(0, flag.find_first_not_of(' '));
            flag.erase(flag.find_last_not_of(' ') + 1);

            if (!Utils::CheckName(flag))
            {
                Utils::PrintException(IllegalVarNameException(0), flag);
                continue;
            }

            string content = input.substr(equal_pos + 1, input.length());

            content.erase(0, content.find_first_not_of(' '));
            content.erase(content.find_last_not_of(' ') + 1);

            try
            {
                auto expr = Parser(Lexer(content).GetTokens(), content, vars).GenExpr()->Simplify();
                auto res = vars->insert(make_pair(flag, expr));
                if (!res.second)
                    (*res.first).second = expr;
                continue;
            }
            catch (Exception e)
            {
                Utils::PrintException(e, content);
            }
            catch (...)
            {
                Utils::PrintException(Exception("Unknown Exception.", -2), content);
            }
        }
        else
        {
            string content = input;

            content.erase(0, content.find_first_not_of(' '));
            content.erase(content.find_last_not_of(' ') + 1);

            try
            {
                auto expr = Parser(Lexer(content).GetTokens(), content, vars).GenExpr()->Simplify();
                Utils::PrintExpr(expr, content);
                continue;
            }
            catch (Exception e)
            {
                Utils::PrintException(e, content);
            }
            catch (...)
            {
                Utils::PrintException(Exception("Unknown Exception.", -2), content);
            }
        }
    }

    delete vars;
    return 0;
}

