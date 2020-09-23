#pragma once
#include<string>
#include<exception>

class NoMoveAllowed : public std::exception
{
    public:
        NoMoveAllowed(const std::string& text) : err_text{text}
        {}

        const char* what() const noexcept()
        {
            return err_text;
        }

    private:
        const std::string err_text;
}