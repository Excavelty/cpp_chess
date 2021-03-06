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

    static Move GetMoveFromString(const std::string& move_str)
    {
        Position current_pos{move_str.substr(0, 2)};
        Position next_pos{move_str.substr(2, 2)};

        Move move{current_pos, next_pos};

        return move;
    }

    bool operator == (const Move& move) const
    {
        return (previous == move.previous && next == move.next);
    }

    inline void disallowDoubleMove() { double_move_flag = false; }
    
    inline void setTakeFlag(bool val)
    {
        take_flag = val;
    }

    inline bool isTake() const { return take_flag; } 


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