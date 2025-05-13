/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Utils
*/

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <vector>
#include <iostream>

class Utils {
    public:
        static bool strIsDigit(std::string str);
        static std::vector<std::string> strToWordArray(std::string str, std::string delims);
};

#endif
