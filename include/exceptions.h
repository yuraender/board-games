#ifndef BG_EXCEPTIONS_H
#define BG_EXCEPTIONS_H

#include <exception>

class IncorrectPositionException : public std::exception {

    const char* what() const noexcept override {
        return "Incorrect position";
    }
};

class UnsupportedOperationException : public std::exception {

    const char* what() const noexcept override {
        return "Unsupported operation";
    }
};

#endif //BG_EXCEPTIONS_H
