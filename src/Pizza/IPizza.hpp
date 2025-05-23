/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** IPizza
*/

#ifndef IPIZZA_HPP_
    #define IPIZZA_HPP_

    #include "Stock.hpp"

enum PizzaType {
    Regina = 1,
    Margarita = 2,
    Americana = 4,
    Fantasia = 8
};

enum PizzaSize {
    S = 1,
    M = 2,
    L = 4,
    XL = 8,
    XXL = 16
};

class IPizza {
    public:
        virtual ~IPizza() = default;

        virtual int getCookTime() const = 0;
        virtual std::string getSize() const = 0;
        virtual std::string getName() const = 0;

        virtual bool canCook(Stock& stock) = 0;
        virtual void cook(Stock& stock) = 0;
};

#endif
