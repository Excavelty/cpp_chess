#pragma once
#include <string>

struct Position
{
    Position() = default;

    Position(const std::string& string_pos) : x{string_pos[0]}, y{std::stoi(string_pos[1])}
    {

    }

    Position(char init_x, int init_y) : x{init_x}, y{init_y}
    {

    }

    char x;
    int y;
};