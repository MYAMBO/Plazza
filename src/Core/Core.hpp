/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Parsing
*/

#ifndef PARSING_HPP_
#define PARSING_HPP_

#include <functional>

#include "Logger.hpp"
#include "Kitchen.hpp"

class Core {
    public:
        Core(size_t cookNumber, int regenerateTime, int cookTime);
        ~Core() = default;

        void parse();
        void handleCommand(std::vector<std::string> wordArray);
        void handlePizza(std::string type, std::string size, int nb);
    private:
        std::unordered_map<std::string, PizzaSize> _pizzaSizeList;
        std::unordered_map<std::string, std::function<std::shared_ptr<IPizza>(std::string)>> _pizzaNameList;

        Kitchen _kitchen; // only one for now
        std::atomic<bool> _isRunning;

};

#endif
