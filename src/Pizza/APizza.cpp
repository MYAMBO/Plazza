/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** APizza
*/

#include "APizza.hpp"

APizza::APizza(std::string size)
{
    _size = size;
}

int APizza::getCookTime() const
{
    return _cookTime;
}

std::string APizza::getSize() const
{
    return _size;
}

std::string APizza::getName() const
{
    return _name;
}

bool APizza::canCook(Stock& stock)
{
    for (auto& elt : stock.getIngredients())
        if (_pizzaIngredients.find(elt.first) != _pizzaIngredients.end())
            if (elt.second == 0)
                return false;
    return true;
}

void APizza::cook(Stock& stock)
{
    for (auto& elt : stock.getIngredients())
        if (_pizzaIngredients.find(elt.first) != _pizzaIngredients.end())
            elt.second--;
}
