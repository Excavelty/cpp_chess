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

    inline void disallow_double_move() { double_move_flag = false; }
    
    inline void set_take_flag(bool val = true)
    {
        take_flag = val;
    }

    inline bool is_take() const { return take_flag; } 


public:
    Position previous;
    Position next;
    
private:
    bool take_flag = false;
    bool check_flag = false;
    bool check_mate_flag = false;
    bool double_move_flag = true;
    bool en_passant_flag = false;
};

inline std::ostream& operator << (std::ostream& out, const Move& move)
{
    return out<<move.previous<<move.next;
}