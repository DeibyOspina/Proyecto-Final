#pragma once

#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>

using namespace std;

class FilesController
{
private:
    fstream file;

public:
    FilesController(string ruta, bool write = false);
    vector<vector<string>> readCSV(char rowSeparator = '\n', string cellSeparator = ";");
    void writeCSV(vector<vector<string>> data, char rowSeparator = '\n', string cellSeparator = ";");
};

FilesController::FilesController(string ruta, bool write)
{
    filesystem::path path(ruta);
    if (filesystem::exists(path) || write)
    {
        if (write)
        {
            file = fstream(ruta, ios::out);
        }
        else
        {
            file = fstream(ruta);
        }

        if (!file.is_open())
        {
            throw runtime_error("Error al abrir el archivo");
        }
    }
    else
    {
        throw runtime_error("La ruta no existe");
    }
}

vector<vector<string>> FilesController::readCSV(char rowSeparator, string cellSeparator)
{
    vector<vector<string>> data;
    vector<string> row;
    string line;

    string cellRegexStr = R"((?:[^;"]*"(?:[^"]|"")*"[^;"]*|[^;"]+)(?=[;,]|$))";
    cellRegexStr = regex_replace(cellRegexStr, regex(";"), cellSeparator);

    regex bomRegex(R"(^\xEF\xBB\xBF)");
    regex cellRegex(cellRegexStr);
    regex cellScapeRegex(R"(.*?)");
    smatch match;

    while (getline(file, line, rowSeparator))
    {
        row.clear();
        auto inicio = sregex_iterator(line.begin(), line.end(), cellRegex);
        auto fin = sregex_iterator();
        for (sregex_iterator i = inicio; i != fin; ++i)
        {
            string cell = (*i).str();
            if (regex_match(cell, match, cellScapeRegex))
            {
                cell = regex_replace(cell, regex("\""), "");
            }
            cell = regex_replace(cell, bomRegex, "");
            row.push_back(cell);
        }
        data.push_back(row);
    }
    return data;
}

void FilesController::writeCSV(vector<vector<string>> data, char rowSeparator, string cellSeparator)
{
    for (vector<string> row : data)
    {
        for (string cell : row)
        {
            file << cell << cellSeparator;
        }
        file << rowSeparator;
    }
}
