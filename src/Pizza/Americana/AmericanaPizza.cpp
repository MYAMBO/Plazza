/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** AmericanaPizza
*/

#include "AmericanaPizza.hpp"

AmericanaPizza::AmericanaPizza(std::string size)
    :APizza(size)
{
    _cookTime = 2;
    _name = "Americana";
    _type = PizzaType::Americana;
    _pizzaIngredients = {"dough", "tomato", "gruyere", "steak"};
}
