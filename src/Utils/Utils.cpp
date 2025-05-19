/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Utils
*/

#include "Utils.hpp"

bool Utils::strIsDigit(std::string str)
{
    for (std::size_t i = 0; i < str.length(); i++)
        if (!isdigit(str[i]))
            return false;
    return true;
}

std::vector<std::string> Utils::strToWordArray(std::string str, std::string delims)
{
    std::vector<std::string> wordArray;
    std::string tmp;

    for (char c : str) {
        if (delims.find(c) != std::string::npos) {
            if (!tmp.empty()) {
                wordArray.push_back(tmp);
                tmp.clear();
            }
        } else
            tmp += c;
    }
    if (!tmp.empty())
        wordArray.push_back(tmp);
    return wordArray;
}
