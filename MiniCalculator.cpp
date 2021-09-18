#include <iostream>
#include <string>
#include <map>

#include "Parser.h"
#include "Expr.h"
#include "Test.cpp"

using namespace MiniCalculator;
using namespace std;

int main()
{
    Utils::Init();

    auto vars = new std::map<std::string, std::shared_ptr<Expr>>();

    string input;
    string flag, content, param;
    int equal_pos = -1;
    double x;
    
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

        equal_pos = input.find('=');
        if (equal_pos != input.npos)
        {
            flag = input.substr(0, equal_pos);

            // trim
            flag.erase(0, flag.find_first_not_of(' '));
            flag.erase(flag.find_last_not_of(' ') + 1);

            string content = input.substr(equal_pos + 1, input.length());

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
                Utils::PrintException(Exception("Unknown Exception.", 0), content);
            }
        }

        auto iter = vars->find(input);
        if (iter != vars->end())
        {
            cout << " | " << (*iter).first << " = " << (*iter).second->Eval() << endl;
            continue;
        }

        int d_pos = input.find('\'');
        if (d_pos != input.npos)
        {
            flag = input.substr(0, d_pos);
            auto flag_iter = vars->find(flag);
            if (flag_iter != vars->end())
                cout << " | " << input << " = " << (*flag_iter).second->Eval().Derivative() << endl;
            continue;
        }

        int paren_lpos = input.find('(');
        int paren_rpos = input.find(')');

        if (paren_lpos != input.npos && paren_rpos != input.npos && paren_rpos > paren_lpos)
        {
            flag = input.substr(0, paren_lpos);
            param = input.substr(paren_lpos + 1, paren_rpos - paren_lpos - 1);

            auto flag_iter = vars->find(flag);
            auto param_iter = vars->find(param);

            if (flag_iter == vars->end())
                continue;

            if (param_iter != vars->end())
            {
                cout << " | " << input << " = " << (*flag_iter).second->Eval((*param_iter).second->Eval()) << endl;
                continue;
            }

            try
            {
                x = stod(param);
                cout << " | " << input << " = " << (*flag_iter).second->Eval(x) << endl;
                continue;
            }
            catch (...)
            {
                Utils::PrintException(UnexpectedNumberException(0), param);
            }
        }
    }

    delete vars;
    return 0;
}

