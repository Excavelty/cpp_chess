#pragma once
#include <exception>

class NoPieceFoundException : public std::exception
{
    public:
        const char* what() const noexcept
        {
            return "Can't find piece on the given position";
        }
};