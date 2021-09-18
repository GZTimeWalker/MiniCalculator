#include "Utils.h"
#include "Token.h"

namespace MiniCalculator
{
	void Utils::SetColor(Color color)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)color);
	}

	void Utils::Init()
	{
		SetColor(Color::BLUE);
		const char* strs[] = {
			"========================================================================================",
			"  ______             __                      __              __                         ",
			" /      \\           /  |                    /  |            /  |                        ",
			"/$$$$$$  |  ______  $$ |  _______  __    __ $$ |  ______   _$$ |_     ______    ______  ",
			"$$ |  $$/  /      \\ $$ | /       |/  |  /  |$$ | /      \\ / $$   |   /      \\  /      \\ ",
			"$$ |       $$$$$$  |$$ |/$$$$$$$/ $$ |  $$ |$$ | $$$$$$  |$$$$$$/   /$$$$$$  |/$$$$$$  |",
			"$$ |   __  /    $$ |$$ |$$ |      $$ |  $$ |$$ | /    $$ |  $$ | __ $$ |  $$ |$$ |  $$/ ",
			"$$ \\__/  |/$$$$$$$ |$$ |$$ \\_____ $$ \\__$$ |$$ |/$$$$$$$ |  $$ |/  |$$ \\__$$ |$$ |      ",
			"$$    $$/ $$    $$ |$$ |$$       |$$    $$/ $$ |$$    $$ |  $$  $$/ $$    $$/ $$ |      ",
			" $$$$$$/   $$$$$$$/ $$/  $$$$$$$/  $$$$$$/  $$/  $$$$$$$/    $$$$/   $$$$$$/  $$/       ",
			"                                                                                        ",
			"========================================================================================",
		};
		for (auto& str : strs)
			PrintLine(str);

		PrintLine("\n  Type 'help' for help.\n", Color::WHITE);
	}

	std::string Utils::GetTypeString(TokenType type)
	{
		switch (type)
		{
		case MiniCalculator::TokenType::LEFT_PAREN:
			return "Left Paren";
		case MiniCalculator::TokenType::RIGHT_PAREN:
			return "Right Paren";
		case MiniCalculator::TokenType::MONOMIAL:
			return "Monomial";
		case MiniCalculator::TokenType::PLUS:
			return "Plus";
		case MiniCalculator::TokenType::MINUS:
			return "Minus";
		case MiniCalculator::TokenType::STAR:
			return "Star";
		case MiniCalculator::TokenType::VAR:
			return "Variable";
		case MiniCalculator::TokenType::NONE:
		default:
			return "Unknown";
		}
	}

	void Utils::Print(std::string msg)
	{
		std::cout << msg;
	}

	void Utils::Print(std::string msg, Color color)
	{
		SetColor(color);
		std::cout << msg;
	}

	void Utils::PrintHelp()
	{
		PrintLine("\nMiniCalculator Version 1.0\n", Color::YELLOW);
		SetColor(Color::WHITE);
		const char* strs[] = {
			"Usage: [Command] or [Variable] = [Expression] | [Number]\n",
			"help:",
			"  Get helps.\n",
			"exit:",
			"  Exit this program.\n",
			"Usage Example:\n",
		};
		for (auto& str : strs)
			PrintLine(str);

		SetColor(Color::CYAN);
		const char* _strs[] = {
			" > f = 4x^3 + 3 - 5x(x + 5 - x^2)",
			" > g = (x + 1)(x - 1) + 6x - 4",
			" > a = (x + 2)",
			" > h = f + g(a) + 4x - 5",
			" > h",
			" | h = 9.00 - 11.00x - 4.00x^2 + 9.00x^3",
			" > h(3)",
			" | h(3) = 183.00",
			" > h(a)",
			" | h(a) = 43.00 + 81.00x + 50.00x^2 + 9.00x^3",
			" > f'",
			" | f' = - 25.00 - 10.00x + 27.00x^2",
			" > s = g(g(a))",
			" > s",
			" | s = 182.00 + 280.00x + 128.00x^2 + 20.00x^3 + x^4",
			" > u = s(x^2)",
			" > u",
			" | u = 182.00 + 280.00x^2 + 128.00x^4 + 20.00x^6 + x^8"
		};
		for (auto& str : _strs)
			PrintLine(str);

		return;
	}

	void Utils::PrintLine(const char* msg)
	{
		std::cout << msg << std::endl;
	}

	void Utils::PrintLine(std::string msg)
	{
		std::cout << msg << std::endl;
	}

	void Utils::PrintLine(std::string msg, Color color)
	{
		SetColor(color);
		std::cout << msg << std::endl;
	}

	void Utils::PrintException(Exception e, std::string source)
	{
		PrintLine("An exception has occurred!", Color::RED);
		PrintLine(e.descr, Color::YELLOW);

		unsigned int pos = e.pos;
		unsigned int rpos = e.pos;
		unsigned int begin = 0;
		unsigned int end = source.length();

		std::string msg = " > ";

		if (e.pos < 0)
			pos = end;

		if (pos - 15 < end)
		{
			begin = pos - 15;
			rpos = pos - begin;
			msg += "...";
		}
		else
			msg += "   ";

		if (pos + 15 < end)
		{
			end = pos + 15;
			msg += source.substr(begin, end - begin);
			msg += "...";
		}
		else
			msg += source.substr(begin, end - begin);

		PrintLine(msg, Color::YELLOW);

		msg.clear();

		if (e.pos == -1)
			rpos = source.length();

		msg += " At   ";
		for (unsigned int i = 0; i < rpos; ++i)
			msg += " ";
		msg += "^ Here";

		PrintLine(msg, Color::CYAN);

		PrintLine("\n", Color::WHITE);
	}
}

