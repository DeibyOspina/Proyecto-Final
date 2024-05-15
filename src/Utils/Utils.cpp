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
    static string getLine(string &line);
    static int getLine(int &line);
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

string Utils::getLine(string &line)
{
    try
    {
        if (getline(cin, line))
        {
            if (cin.rdbuf()->in_avail() > 1)
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            return line;
        }
        else
        {
            cerr << "Error: Fallo al leer la línea." << endl;
        }
    }
    catch (const exception &e)
    {
        cerr << e.what() << endl;
    }
    return "";
}

int Utils::getLine(int &line)
{
    cin >> line;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return line;
}

void Utils::clearScreen()
{
    cout << "\033[2J\033[1;1H";
}