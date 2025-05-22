/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** MargaritaPizza
*/

#ifndef MARGARITA_HPP_
    #define MARGARITA_HPP_

    #include "APizza.hpp"

class MargaritaPizza : public APizza {
    public:
        MargaritaPizza(PizzaSize);
        ~MargaritaPizza() = default;
};

#endif
