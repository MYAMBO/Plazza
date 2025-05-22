/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** AmericanaPizza
*/

#include "AmericanaPizza.hpp"

AmericanaPizza::AmericanaPizza(PizzaSize size)
    :APizza(size)
{
    _name = "Americana";
    _type = PizzaType::Americana;
    _pizzaIngredients = {"dough", "tomato", "gruyere", "steak"};
}
