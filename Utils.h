#pragma once


#include <Windows.h>
#include <string>
#include <map>
#include "Exception.h"

namespace MiniCalculator
{

    enum class TokenType;
    /// <summary>
    /// An enumeration of available colors.
    /// </summary>
    enum class Color : int
    {
        ORIGIN = FOREGROUND_INTENSITY,
        RED = FOREGROUND_INTENSITY | FOREGROUND_RED,
        GREEN = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
        BLUE = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
        CYAN = FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN,
        YELLOW = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
        PINK = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
        WHITE = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,

        B_ORIGIN = BACKGROUND_INTENSITY,
        B_RED = BACKGROUND_INTENSITY | BACKGROUND_RED,
        B_GREEN = BACKGROUND_INTENSITY | BACKGROUND_GREEN,
        B_BLUE = BACKGROUND_INTENSITY | BACKGROUND_BLUE,
        B_CYAN = BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN,
        B_YELLOW = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN,
        B_PINK = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE,
        B_WHITE = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
    };

    /// <summary>
    /// Utils class.
    /// </summary>
    class Utils
    {
    public:

        /// <summary>
        /// Sets the output text color.
        /// </summary>
        /// <param name="color">color enumeration value</param>
        static void SetColor(Color color);

        static void Init();
        static std::string GetTypeString(TokenType type);

        static void Print(std::string msg);
        static void Print(std::string msg, Color color);

        static void PrintHelp();

        static void PrintLine(std::string msg);
        static void PrintLine(const char* msg);
        static void PrintLine(std::string msg, Color color);
        static void PrintException(Exception e, std::string source);
    };
}
