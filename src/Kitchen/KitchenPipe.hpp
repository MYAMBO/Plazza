/*
** EPITECH PROJECT, 2025
** KitchenPipe.hpp
** File description:
** KitchenPipe.hpp
** created and edited by antoiix.
** All rights reserved
*/

#ifndef KITCHENPIPE_HPP
#define KITCHENPIPE_HPP

#include <string>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

class KitchenPipe
{
public:
    explicit KitchenPipe(const std::string &path, bool writeMode = false);
    ~KitchenPipe();

    KitchenPipe& operator<<(const std::string &message);
    KitchenPipe& operator>>(std::string &message);

private:
    int _fd;
    std::string _path;
    bool _writeMode;
};

#endif //KITCHENPIPE_HPP
