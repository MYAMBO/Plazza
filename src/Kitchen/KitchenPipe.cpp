/*
** EPITECH PROJECT, 2025
** KitchenPipe.cpp
** File description:
** KitchenPipe.cpp
** created and edited by antoiix.
** All rights reserved
*/

#include "KitchenPipe.hpp"

#include <iostream>
#include <unistd.h>

KitchenPipe::KitchenPipe(const std::string& path, bool writeMode)
{
    this->_path = path;
    this->_writeMode = writeMode;

    // mkfifo(this->_path.c_str(), 0666);
    if (writeMode)
        this->_fd = open(this->_path.c_str(), O_WRONLY);
    else
        this->_fd = open(this->_path.c_str(), O_RDONLY);
}

KitchenPipe::~KitchenPipe()
{
    if (this->_fd >= 0)
        close(this->_fd);
}

KitchenPipe& KitchenPipe::operator<<(const std::string& message)
{
    if (this->_writeMode)
        write(this->_fd, (message + "\r\n").c_str(), (message + "\r\n").size());
    return *this;
}

KitchenPipe& KitchenPipe::operator>>(std::string& message)
{
    char buffer[BUFFER_SIZE] = {0};
    read(this->_fd, buffer, BUFFER_SIZE);
    message.append(buffer);
    while (message.find("\r\n") == std::string::npos)
    {
        read(this->_fd, buffer, BUFFER_SIZE);
        message.append(buffer);
    }
    message.erase(message.find("\r\n"));
    return *this;
}