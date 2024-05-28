#pragma once

#include <iostream>
#include <regex>
#include <limits>
#include <iomanip>
#include <ctime>
#include <sstream>

using namespace std;

class Utils
{
public:
    Utils();
    static string toLowerCase(string &text);
    static bool isDate(string &date);
    static string getLine(string &line);
    static auto cinIgnore();
    static void clearScreen();
    static string getCurrentDate();
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


void Utils::clearScreen()
{
    cout << "\033[2J\033[1;1H";
}

string Utils::getCurrentDate()
{
    auto t = time(nullptr);
    ostringstream oss;
    oss << put_time(localtime(&t), "%d/%m/%Y %H:%M:%S");
    return oss.str();
}
