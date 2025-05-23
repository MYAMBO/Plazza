/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** ReginaPizza
*/

#include "ReginaPizza.hpp"

ReginaPizza::ReginaPizza(std::string size)
    :APizza(size)
{
    _cookTime = 2;
    _name = "regina";
    _type = PizzaType::Regina;
    _pizzaIngredients = {"dough", "tomato", "gruyere", "ham", "mushrooms"};
}
