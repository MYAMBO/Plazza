/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** AmericanaPizza
*/

#ifndef AMERICANA_HPP_
    #define AMERICANA_HPP_

    #include "APizza.hpp"

class AmericanaPizza : public APizza {
    public:
        AmericanaPizza(PizzaSize);
        ~AmericanaPizza() = default;
};

#endif
