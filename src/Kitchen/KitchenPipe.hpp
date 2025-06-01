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
#include <memory>

#define BUFFER_SIZE 1024

class KitchenPipe
{
public:
    explicit KitchenPipe(const std::string &path, bool writeMode = false);
    ~KitchenPipe();

    std::string _path;

    KitchenPipe& operator<<(const std::string &message);
    KitchenPipe& operator>>(std::string &message);

private:
    int _fd;
    bool _writeMode;
};

struct KitchenHandle {
    pid_t pid{};
    std::string fifoPath;
    std::unique_ptr<KitchenPipe> toKitchenPipe;
    std::unique_ptr<KitchenPipe> toReceptionPipe;
    bool isClosed = false;

    KitchenHandle() = default;

    KitchenHandle(pid_t p, const std::string& path)
        : pid(p), fifoPath(path), toKitchenPipe(std::make_unique<KitchenPipe>(path, true)), toReceptionPipe(std::make_unique<KitchenPipe>(path, true)) {}
};

#endif //KITCHENPIPE_HPP
