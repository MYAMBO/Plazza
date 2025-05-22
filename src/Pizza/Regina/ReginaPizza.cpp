/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** ReginaPizza
*/

#include "ReginaPizza.hpp"

ReginaPizza::ReginaPizza(PizzaSize size)
    :APizza(size)
{
    _name = "regina";
    _type = PizzaType::Regina;
    _pizzaIngredients = {"dough", "tomato", "gruyere", "ham", "mushrooms"};
}
