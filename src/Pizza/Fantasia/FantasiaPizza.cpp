/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** FantasiaPizza
*/

#include "FantasiaPizza.hpp"

FantasiaPizza::FantasiaPizza(std::string size)
    :APizza(size)
{
    _cookTime = 4;
    _name = "Fantasia";
    _type = PizzaType::Fantasia;
    _pizzaIngredients = {"dough", "tomato", "eggplant", "goatCheese", "chiefLove"};
}
