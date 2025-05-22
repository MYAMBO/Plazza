/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Kitchen
*/

#include <chrono>
#include <iostream>

#include "Kitchen.hpp"

Kitchen::Kitchen(std::size_t cookNumber, int regenerateTime)
    :_regeneratorThread(regenerator, std::ref(_stock), regenerateTime)
{
    _cookNumber = cookNumber;
}

Kitchen::~Kitchen()
{
    _regeneratorThread.detach();
}

void Kitchen::regenerator(Stock& stock, int regenerateTime)
{
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(regenerateTime));
        stock.IncrementAll();
    }
}

Stock& Kitchen::getStock()
{
    return _stock;
}

void Kitchen::printIngredient()
{
    for (auto elt : _stock.getIngredients())
        std::cout << elt.first << " : " << elt.second << "\n";
}
