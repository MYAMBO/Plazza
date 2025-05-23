/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** MargaritaPizza
*/

#include "MargaritaPizza.hpp"

MargaritaPizza::MargaritaPizza(std::string size)
    :APizza(size)
{
    _cookTime = 1;
    _name = "Margarita";
    _type = PizzaType::Margarita;
    _pizzaIngredients = {"dough", "tomato", "gruyere"};
}
