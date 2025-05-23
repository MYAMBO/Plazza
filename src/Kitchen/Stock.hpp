/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Stock
*/

#ifndef STOCK_HPP_
    #define STOCK_HPP_

    #include <map>
    #include <string>

class Stock {
    public:
        Stock();
        ~Stock() = default;

        void IncrementAll();
        std::map<std::string, int>& getIngredients();
    private:
        std::map<std::string, int> _ingredients;
};

#endif
