/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** FantasiaPizza
*/

#include "FantasiaPizza.hpp"

FantasiaPizza::FantasiaPizza(PizzaSize size)
    :APizza(size)
{
    _name = "Fantasia";
    _type = PizzaType::Fantasia;
    _pizzaIngredients = {"dough", "tomato", "eggplant", "goatCheese", "chiefLove"};
}
