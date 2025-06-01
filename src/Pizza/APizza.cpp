/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** APizza
*/

#include "APizza.hpp"
#include <sstream>

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

std::string APizza::pack() const
{
    return std::to_string(static_cast<int>(_type)) + " " +
               std::to_string(std::stoi(_size));
}

APizza unpack(const std::string& data) {
    std::istringstream iss(data);
    int t, s;
    if (!(iss >> t >> s)) {
        throw std::runtime_error("Invalid pizza format: " + data);
    }

    return APizza{
        std::to_string(t)
    };
}