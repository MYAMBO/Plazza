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

    KitchenPipe& operator<<(const std::string &message);
    KitchenPipe& operator>>(std::string &message);

private:
    int _fd;
    std::string _path;
    bool _writeMode;
};

struct KitchenHandle {
    pid_t pid{};
    std::string fifoPath;
    std::unique_ptr<KitchenPipe> pipe;
    bool isClosed = false;

    KitchenHandle() = default;

    KitchenHandle(pid_t p, const std::string& path)
        : pid(p), fifoPath(path), pipe(std::make_unique<KitchenPipe>(path, true)) {}

    void send(const std::string& msg) {
        if (pipe)
            (*pipe) << msg;
    }

    void close() {
        if (pipe) {
            pipe.reset();
        }
    }
};

#endif //KITCHENPIPE_HPP
