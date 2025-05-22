/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** APizza
*/

#ifndef APIZZA_HPP_
    #define APIZZA_HPP_

    #include <unordered_set>

    #include "IPizza.hpp"

class APizza : public IPizza {
    public:
        APizza(PizzaSize size);
        ~APizza() = default;

        std::string getName() const;
        void cook(Stock& stock);
    protected:
        PizzaType _type;
        PizzaSize _size;
        std::string _name;
        std::unordered_set<std::string> _pizzaIngredients;
};

#endif
