/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Kitchen
*/

#ifndef KITCHEN_HPP_
    #define KITCHEN_HPP_

    #include <thread>

    #include "Stock.hpp"

class Kitchen {
    public:
        Kitchen(std::size_t cookNumber, int regenerateTime);
        ~Kitchen();

        Stock& getStock();
        void printIngredient();
    private:
        static void regenerator(Stock& stock, int regenerateTime);

        std::size_t _cookNumber;

        Stock _stock;
        std::thread _regeneratorThread;
};

#endif
