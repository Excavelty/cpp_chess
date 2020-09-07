#pragma once
#include "Piece.h"

class Knight : public Piece 
{
    public:
        Knight(const char sign = 'P') : Piece{sign}
        {}

        std::vector<Move> get_allowed_moves() const final
        {
            std::vector<Move> moves;
            const int change_vectors[8][2] = {{-2, -1}, {-2, 1}, {2, -1}, {2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}};

            for(int i = 0; i < 8; ++i)
            {
                Position possible_pos{change_vectors[i][0], change_vectors[i][1]};
                if(on_board(possible_pos))
                    moves.push_back(Move{pos, possible_pos});
            }

            return moves; //start from here, think of allowed moves for knight, and packing code
        }

};