/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Parsing
*/

#ifndef PARSING_HPP_
    #define PARSING_HPP_

    #include <functional>

    #include "Kitchen.hpp"

class Core {
    public:
        Core(size_t cookNumber, int regenerateTime, int cookTime);
        ~Core() = default;

        void parse();
        void handleCommand(std::vector<std::string> wordArray);
        void handlePizza(std::string type, std::string size, int nb);
        void spawnKitchen(int index);
    private:
        std::unordered_map<std::string, PizzaSize> _pizzaSizeList;
        std::unordered_map<std::string, std::function<std::shared_ptr<IPizza>(std::string)>> _pizzaNameList;

        std::vector<KitchenHandle> _kitchens;
        std::size_t _cookNumber;
        int _regenerateTime;
        int _cookTime;
        std::atomic<bool> _isRunning;
        int _kitchenIndex;

};

#endif
