#pragma once
#include "Pos.h"

class Move
{
public:
    Move(const std::string& prev, const std::string& n) : previous{prev}, next{n} 
    {

    }

    Move(const Position& pos1, const Position& pos2) : previous{pos1}, next{pos2} 
    {

    }

    bool operator == (const Move& move) const
    {
        return (previous == move.previous && next == move.next);
    }

    inline void disallow_double_move() { double_move = false;}


public:
    Position previous;
    Position next;
    
private:
    bool is_take = false;
    bool is_check = false;
    bool is_check_mate = false;
    bool double_move = true;
    bool en_passant = false;
};

inline std::ostream& operator << (std::ostream& out, const Move& move)
{
    return out<<move.previous<<move.next;
}