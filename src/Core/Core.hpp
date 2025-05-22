/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Parsing
*/

#ifndef PARSING_HPP_
#define PARSING_HPP_

#include <string>
#include <functional>
#include <unordered_map>

#include "IPizza.hpp"
#include "Kitchen.hpp"

class Core {
    public:
        Core(size_t cookNumber, int regenerateTime);
        ~Core() = default;

        void parse();
        void handleCommand(std::vector<std::string> wordArray);
        void handlePizza(std::string type, std::string size, int nb);
    private:
        std::unordered_map<std::string, std::function<std::unique_ptr<IPizza>(PizzaSize)>> _pizzaNameList;
        std::unordered_map<std::string, PizzaSize> _pizzaSizeList;

        Kitchen _kitchen; // only one for now
};

#endif
