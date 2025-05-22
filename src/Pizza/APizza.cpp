/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** APizza
*/

#include "APizza.hpp"

APizza::APizza(PizzaSize size)
{
    _size = size;
}

std::string APizza::getName() const
{
    return _name;
}

void APizza::cook(Stock& stock)
{
    for (auto& elt : stock.getIngredients())
        if (_pizzaIngredients.find(elt.first) != _pizzaIngredients.end())
            elt.second--;
    (void) stock;
}
