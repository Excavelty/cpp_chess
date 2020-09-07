#pragma once
#include <Pos.h>

struct Move
{
    Move(const std::string& prev, const std::string& n) : previous{prev}, next{n} 
    {

    }

    Move(const Position& pos1, const Position& pos2) : previous{pos1}, next{pos2} 
    {

    }

    Position previous;
    Position next;
};