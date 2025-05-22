/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** MargaritaPizza
*/

#include "MargaritaPizza.hpp"

MargaritaPizza::MargaritaPizza(PizzaSize size)
    :APizza(size)
{
    _name = "Margarita";
    _type = PizzaType::Margarita;
    _pizzaIngredients = {"dough", "tomato", "gruyere"};
}
