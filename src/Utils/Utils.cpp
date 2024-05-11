#pragma once
#include <iostream>
#include <regex>
#include <limits>
using namespace std;

class Utils
{
public:
    Utils();
    static string toLowerCase(string &text);
    static bool isDate(string &date);
    static auto getLine(string &line);
    static auto getLine(int &line);
    static auto cinIgnore();
    static void clearScreen();
};

Utils::Utils()
{
}

string Utils::toLowerCase(string &text)
{
    string lowerCaseText = "";
    for (int i = 0; i < text.size(); i++)
    {
        lowerCaseText += tolower(text[i]);
    }
    return lowerCaseText;
}

bool Utils::isDate(string &date)
{
    regex dateRegex("^([0-2][0-9]|3[0-1])(\\/)(0[1-9]|1[0-2])\\2(\\d{4})$");
    smatch match;
    return regex_match(date, match, dateRegex);
}

auto Utils::cinIgnore()
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

auto Utils::getLine(string &line)
{
    cinIgnore();
    getline(cin, line);
    return line;
}

auto Utils::getLine(int &line)
{
    cinIgnore();
    cin >> line;
    return line;
}

void Utils::clearScreen()
{
    cout << "\033[2J\033[1;1H";
}