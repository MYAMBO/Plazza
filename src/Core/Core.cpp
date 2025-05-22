/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Core
*/

#include <iostream>

#include "Core.hpp"
#include "Utils.hpp"
#include "Regina/ReginaPizza.hpp"
#include "Fantasia/FantasiaPizza.hpp"
#include "Margarita/MargaritaPizza.hpp"
#include "Americana/AmericanaPizza.hpp"

Core::Core(size_t cookNumber, int regenerateTime)
    :_kitchen(cookNumber, regenerateTime)
{
    _pizzaNameList["regina"] = [](PizzaSize size) { return std::make_unique<ReginaPizza>(size); };
    _pizzaNameList["fantasia"] = [](PizzaSize size) { return std::make_unique<FantasiaPizza>(size); };
    _pizzaNameList["margarita"] = [](PizzaSize size) { return std::make_unique<MargaritaPizza>(size); };
    _pizzaNameList["americana"] = [](PizzaSize size) { return std::make_unique<AmericanaPizza>(size); };

    _pizzaSizeList.emplace("S", PizzaSize::S);
    _pizzaSizeList.emplace("M", PizzaSize::M);
    _pizzaSizeList.emplace("L", PizzaSize::L);
    _pizzaSizeList.emplace("XL", PizzaSize::XL);
    _pizzaSizeList.emplace("XXL", PizzaSize::XXL);
}

void Core::handlePizza(std::string type, std::string size, int nb)
{
    std::cout << "type: " << type << std::endl;
    std::cout << "taille: " << size << std::endl;
    std::cout << "nombre: " << nb << std::endl;
    
    auto pizza = _pizzaNameList[type](_pizzaSizeList[size]);
    pizza->cook(_kitchen.getStock());
}

void Core::handleCommand(std::vector<std::string> wordArray)
{
    if (wordArray.size() != 3) {
        std::cout << "command must be : \"[pizza type] [pizza size] [xn]\" when n is the number of pizza" << std::endl;
        return;
    }
    if (this->_pizzaNameList.find(wordArray[0]) == this->_pizzaNameList.end()) {
        std::cout << "this pizza does not exist" << std::endl;
        return;
    }
    if (this->_pizzaSizeList.find(wordArray[1]) == this->_pizzaSizeList.end()) {
        std::cout << "this size does not exist" << std::endl;
        return;
    }
    std::string strNbWithoutX = wordArray[2].substr(1, wordArray[2].size() - 1);
    if (wordArray[2][0] != 'x' || !Utils::strIsDigit(strNbWithoutX)) {
        std::cout << "number of pizza must be \"xn\" when n is the number of pizza" << std::endl;
        return;
    }
    int nb = std::atoi(strNbWithoutX.c_str());
    if (nb <= 0 || nb >= 100) {
        std::cout << "number of pizza must be a number between 1 and 99" << std::endl;
        return;
    }
    handlePizza(wordArray[0], wordArray[1], nb);
}

void Core::parse()
{
    std::string line;
    std::vector<std::string> wordArray;

    std::cout << "> ";
    while (std::getline(std::cin, line)) {
        if (line == "exit")
            break;
        if (line == "ingredients") {
            _kitchen.printIngredient();
            std::cout << "> ";
            continue;
        }
        wordArray = Utils::strToWordArray(line, " \t");
        handleCommand(wordArray);
        std::cout << "> ";
    }
    std::cout << "exit" << std::endl;
}
