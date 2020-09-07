#pragma once
#include "Pos.h"
#include "Move.h"
#include <string>
#include <vector>

class Piece
{
    public:
        Piece(const char init_sign = 'P') : sign{init_sign}
        {

        }

        virtual ~Piece() = default;

        virtual std::vector<Move> get_allowed_moves() const = 0;
        
        void set_pos(const Position& new_pos)
        {
            pos = new_pos;
        }

        std::string get_pos() const
        {
            return pos;
        }

        void get_sign() const
        {
            return sign;
        }

    protected:
        bool piece_on_board(const Position& pos)
        {
            return (pos.x >= 'a' && pos.x <= 'h' && pos.y >=1 && pos.y <= 8);
        }

    protected:
        char sign;
        Position pos;
};