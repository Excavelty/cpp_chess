#pragma once
#include <string>
#include <iostream>

struct Position
{
    Position() = default;

    Position(const std::string& string_pos) : x{string_pos[0]}, y{string_pos[1] - '0'}
    {

    }

    Position(char init_x, int init_y) : x{init_x}, y{init_y}
    {

    }

    bool operator == (const Position& pos) const
    {
        return (x == pos.x && y == pos.y);
    }

    std::string get_string() const
    {
        return std::string{x} + std::to_string(y);
    }

    char x;
    int y;
};

inline std::ostream& operator << (std::ostream& out, const Position& pos)
{
    return out<<std::string{pos.x}<<" "<<pos.y<<" ";
}