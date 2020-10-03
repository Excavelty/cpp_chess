#pragma once

#include "Piece.h"

class King : public Piece
{
    public:
        King(const char sign, const std::string& init_pos) : Piece{sign, init_pos}
        {}

        std::vector<Move> get_allowed_moves() const final
        {
            std::vector<Move> moves;
            std::vector<Vector2d<int>> change_vectors 
            = {Vector2d<int>{-1, -1}, Vector2d<int>{-1, 1}, Vector2d<int>{-1, 0}, Vector2d<int>{1, 0}, 
               Vector2d<int>{0, -1}, Vector2d<int>{0, 1}, Vector2d<int>{1, -1}, Vector2d<int>{1, 1}};

            moves = get_moves_from_change_vectors(change_vectors);
            return moves;
        }

    private:

};