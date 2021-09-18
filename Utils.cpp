#include "Utils.h"

namespace MiniCalculator
{
	void Utils::SetColor(Color color)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)color);
	}

	void Utils::Init()
	{
		SetColor(Color::BLUE);
		std::string strs[] = {
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
		return;
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

		if (pos - 7 < end)
		{
			begin = pos - 7;
			rpos = pos - begin;
			msg += "...";
		}
		else
			msg += "   ";

		if (pos + 8 < end)
		{
			end = pos + 8;
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
		for (int i = 0; i < rpos; ++i)
			msg += " ";
		msg += "^ Here";

		PrintLine(msg, Color::CYAN);

		PrintLine("\n", Color::WHITE);
	}
}

