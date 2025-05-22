/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** FantasiaPizza
*/

#ifndef FANTASIA_HPP_
    #define FANTASIA_HPP_

    #include "APizza.hpp"

class FantasiaPizza : public APizza {
    public:
        FantasiaPizza(PizzaSize);
        ~FantasiaPizza() = default;
};

#endif
