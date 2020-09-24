#pragma once
#include<string>
#include<exception>

class NoMoveAllowedException : public std::exception
{
    public:
        NoMoveAllowedException(const char* text) : err_text{text}
        {}

        const char* what() const noexcept
        {
            return err_text;
        }

    private:
        const char* err_text;
};