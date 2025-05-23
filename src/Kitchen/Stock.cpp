/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Stock
*/

#include "Stock.hpp"

Stock::Stock()
{
    _ingredients.emplace("ham", 5);
    _ingredients.emplace("dough", 5);
    _ingredients.emplace("steak", 5);
    _ingredients.emplace("tomato", 5);
    _ingredients.emplace("gruyere", 5);
    _ingredients.emplace("eggplant", 5);
    _ingredients.emplace("mushrooms", 5);
    _ingredients.emplace("chiefLove", 5);
    _ingredients.emplace("goatCheese", 5);
}

void Stock::IncrementAll()
{
    for (auto& elt : _ingredients)
        elt.second++;
}

std::map<std::string, int>& Stock::getIngredients()
{
    return _ingredients;
}
