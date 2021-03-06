#pragma once

#include <Windows.h>
#include <string>
#include <map>
#include "Exception.h"

namespace MiniCalculator
{

    enum class TokenType;
    class Expr;
    class Polyomial;
    /// <summary>
    /// 颜色枚举
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
    /// 工具类
    /// </summary>
    class Utils
    {
    public:

        /// <summary>
        /// 设置输出颜色
        /// </summary>
        /// <param name="color">颜色枚举值</param>
        static void SetColor(Color color);

        static bool DEBUG;
        static int DEPTH;

        static void Init();
        static std::string GetTypeString(TokenType type);

        static void Print(std::string msg);
        static void Print(std::string msg, Color color);

        static void PrintHelp();

        static void PrintLine(std::string msg);
        static void PrintLine(const char* msg);
        static void PrintLine(std::string msg, Color color);

        static void PrintDebugLine(bool in, std::string name);

        /// <summary>
        /// 输出表达式
        /// </summary>
        /// <param name="poly">多项式</param>
        /// <param name="input">输入</param>
        static void PrintExpr(Polyomial& poly, std::string& input);
        /// <summary>
        /// 输出表达式
        /// </summary>
        /// <param name="poly">多项式</param>
        /// <param name="token">运算符</param>
        static void PrintDebugExpr(Polyomial poly);
        /// <summary>
        /// 输出表达式
        /// </summary>
        /// <param name="poly">多项式</param>
        /// <param name="token">运算符</param>
        static void PrintDebugExprWithToken(Polyomial poly, TokenType type);
        /// <summary>
        /// 异常处理
        /// </summary>
        /// <param name="e">异常</param>
        /// <param name="source">源字符串</param>
        static void PrintException(Exception e, std::string source);
        /// <summary>
        /// 检查变量名
        /// </summary>
        /// <param name="var">变量名称</param>
        /// <returns>是否可用</returns>
        static bool CheckName(std::string var);
    };

}
