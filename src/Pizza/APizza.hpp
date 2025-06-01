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
        APizza(std::string size);
        ~APizza() = default;

        int getCookTime() const;
        std::string getSize() const;
        std::string getName() const;

        bool canCook(Stock& stock);
        void cook(Stock& stock);
        std::string pack() const;
        APizza unpack() const;
    protected:
        int _cookTime;
        PizzaType _type;
        std::string _size;
        std::string _name;
        std::unordered_set<std::string> _pizzaIngredients;
};

#endif
