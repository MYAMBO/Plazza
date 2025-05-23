/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** ReginaPizza
*/

#ifndef REGINA_HPP_
    #define REGINA_HPP_

    #include "APizza.hpp"

class ReginaPizza : public APizza {
    public:
        ReginaPizza(std::string size);
        ~ReginaPizza() = default;
};

#endif
