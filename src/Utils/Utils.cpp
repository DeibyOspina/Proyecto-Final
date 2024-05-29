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
    static const int SEGUNDOS_POR_DIA = 86400;
    static string toLowerCase(string &text);
    static bool isDate(string &date);
    static string getLine(string &line);
    static void clearScreen();
    static string getCurrentDate();
    static string parseDate(time_t date);
    static time_t parseDate(string date);
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
    cout << "\033[2J\033[1;1H"; //Codigo ANSI para limpiar la pantalla
}

string Utils::getCurrentDate()
{
    auto t = time(nullptr);
    return parseDate(t);
}

string Utils::parseDate(time_t date)
{
    ostringstream oss;
    oss << put_time(localtime(&date), "%d/%m/%Y");
    return oss.str();
}

time_t Utils::parseDate(string date)
{
    tm tm = {};
    istringstream ss(date);
    ss >> get_time(&tm, "%d/%m/%Y");
    return mktime(&tm);
}
