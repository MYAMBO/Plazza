/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Parsing
*/

#ifndef PARSING_HPP_
#define PARSING_HPP_

#include <string>
#include <vector>
#include <unordered_set>

class Core {
    public:
        Core();
        ~Core();

        void parse();
        void handleCommand(std::vector<std::string> wordArray);
    private:
        std::unordered_set<std::string> _pizzaNameList;
        std::unordered_set<std::string> _pizzaSizeList;
};

#endif
