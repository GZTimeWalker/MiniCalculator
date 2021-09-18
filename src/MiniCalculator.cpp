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
                // 语义解析
                if (content.at(content.length() - 1) == '\'')
                {
                    content = content.erase(content.find_last_of('\''));
                    auto expr = Parser(Lexer(content).GetTokens(), content, vars).GenExpr()->Simplify();
                    expr = expr->Eval().Derivative().AsExpr();
                    auto res = vars->insert(make_pair(flag, expr));
                    if (!res.second)
                        (*res.first).second = expr;
                    continue;
                }
                else
                {
                    auto expr = Parser(Lexer(content).GetTokens(), content, vars).GenExpr()->Simplify();
                    auto res = vars->insert(make_pair(flag, expr));
                    if (!res.second)
                        (*res.first).second = expr;
                    continue;
                }
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

        // 输出变量表达式
        auto iter = vars->find(input);
        if (iter != vars->end())
        {
            cout << " | " << (*iter).first << " = " << (*iter).second->Eval() << endl;
            continue;
        }

        // 变量表达式求导
        int d_pos = input.find('\'');
        if (d_pos != input.npos)
        {
            flag = input.substr(0, d_pos);
            auto flag_iter = vars->find(flag);
            if (flag_iter != vars->end())
                cout << " | " << input << " = " << (*flag_iter).second->Eval().Derivative() << endl;
            continue;
        }

        // 变量表达式代入求值
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

            // 复合函数
            if (param_iter != vars->end())
            {
                cout << " | " << input << " = " << (*flag_iter).second->Eval((*param_iter).second->Eval()) << endl;
                continue;
            }

            try
            {
                // 输入数字
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

