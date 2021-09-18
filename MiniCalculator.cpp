#include <iostream>
#include <string>
#include "Parser.h"
#include "Test.cpp"

using namespace MiniCalculator;
using namespace std;

int main()
{
    Utils::Init();

    string input;
    bool stop = false;
    while (!stop)
    {
        Utils::Print(" > ", Color::YELLOW);
        getline(cin, input);
        if (getchar() != '/n')
            break;

        switch (input[0])
        {
        case 'h':
            if(input.find("help") != string.npos)
        default:
            break;
        }
    }

    return 0;
}

