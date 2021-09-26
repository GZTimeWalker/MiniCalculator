#include <iostream>
#include <string>
#include <iomanip>

#include "Expr.h"
#include "Polyomial.h"
#include "Lexer.h"
#include "Parser.h"
#include "Utils.h"

using namespace std;

namespace MiniCalculator
{
	static class Test
	{
	public:
		static void DoPolyomialTest()
		{
			map<int, long double> a = { {1, 2}, {0, 3}, {2,2}, {-2,3} };
			map<int, long double> b = { {0,9}, {1, 4},{2,2} };
			Polyomial apoly(a);
			Polyomial bpoly(b);
			cout << "Poly     a = " << apoly << endl;
			cout << "Poly    a' = " << apoly.Derivative() << endl;
			cout << "Poly     b = " << bpoly << endl;
			cout << "Poly    b' = " << bpoly.Derivative() << endl;
			cout << "Poly a + b = " << apoly + bpoly << endl;
			cout << "Poly a - b = " << apoly - bpoly << endl;
			cout << "Poly a * b = " << apoly * bpoly << endl;
			cout << "Poly (a * b)' = " << (apoly * bpoly).Derivative() << endl;
		}

		/*static void DoLexerTest()
		{
			string input = "2*3+4x^2+(2+3x^1)-6-3x+5x^2(x^7-3)";
			for (auto& item : Lexer(input).GetTokens())
				cout << "pos: " << item.Start << "\t with " << item.GetValue(input) << endl;

			MonomialExpr expr("4.5x^2");
			cout << expr.Eval() << endl;

			expr = MonomialExpr("4.5x");
			cout << expr.Eval() << endl;

			expr = MonomialExpr("4.5");
			cout << expr.Eval() << endl;

			expr = MonomialExpr("x");
			cout << expr.Eval() << endl;

			expr = MonomialExpr("x^3");
			cout << expr.Eval() << endl;

			expr = MonomialExpr("3x");
			cout << expr.Eval() << endl;
		}*/

		static void DoParserTest()
		{
			string _input = "f = 2*3+4x^2+(2+3x^1)-6+6(3x-6x^3)";

			int equal_pos = _input.find('=');
			string flag = _input.substr(0, equal_pos);
			string input = _input.substr(equal_pos + 1, input.length());

			auto tokens = Lexer(input).GetTokens();

			for (auto& item : tokens)
				cout << "pos: " << item.Start << "\t with " << item.GetValue(input) << endl;

			auto ast = Parser(tokens, input, nullptr).GenExpr();

			cout << "f(x) = " << ast->Eval() << endl;
			cout << "f(1) = " << ast->Eval(1) << endl;
			cout << "f(0) = " << ast->Eval(0) << endl;
		}

		static void DoParserTest2()
		{
			string input = "1+x^5";

			auto ast = Parser(Lexer(input).GetTokens(), input, nullptr).GenExpr();

			input = "x+1";

			auto ast1 = Parser(Lexer(input).GetTokens(), input, nullptr).GenExpr();

			cout << "f(x) = " << ast->Eval() << endl;
			cout << "g(x) = " << ast1->Eval() << endl;
			cout << "f(g(x)) = " << ast->Eval(ast1->Eval()) << endl;
			cout << "g(f(x)) = " << ast1->Eval(ast->Eval()) << endl;
		}

		static void DoTest()
		{
			string input;
			long double x;
			while (true)
			{
				try {
					cout << "f(x) = ";

					getline(cin, input);

					auto ast = Parser(Lexer(input).GetTokens(), input, nullptr).GenExpr();

					cout << "Your input: f(x) = " << ast->Eval() << endl;

					for (int i = 0; i < 3; ++i)
					{
						cout << "Test (" << i + 1 << "/3), input x: ";
						cin >> x;
						cout << "f(" << x << ") = " << setiosflags(ios::fixed) << setprecision(2) << ast->Eval(x) << endl;
					}
					char c = getchar();
				}
				catch (Exception e)
				{
					Utils::PrintException(e, input);
				}
			}
		}
	};
}