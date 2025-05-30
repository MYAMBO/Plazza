/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Parsing
*/

#ifndef PARSING_HPP
    #define PARSING_HPP

    #include <vector>

class Parsing {
    public:

        class ParsingError : public std::exception {
            public:
                explicit ParsingError(const std::string &message);

                const char *what() const noexcept override;
            private:
                std::string _message;
        };

        Parsing(char **argv, int argc);
        ~Parsing();

        bool isOnlyInt(std::string str) const;
        int getCookTime() const;
        int getNbCookNumber() const;
        int getRegenerateTime() const;

        static void help();
    private:

        int _cookTime;
        int _nbCookNumber;
        int _regenerateTime;

        std::vector<std::string> _arguments;
};

#endif