#pragma once
#include "Piece.h"

class Knight : public Piece 
{
    public:
        Knight(const char sign, const std::string& init_pos) : Piece{sign, init_pos}
        {}

        std::vector<Move> get_allowed_moves() const final
        {
            std::vector<Move> moves;
            std::vector<Vector2d<int>> change_vectors = 
                {Vector2d<int>{-2, -1}, Vector2d<int>{-2, 1}, Vector2d<int>{2, -1}, Vector2d<int>{2, 1}, 
                Vector2d<int>{-1, -2}, Vector2d<int>{-1, 2}, Vector2d<int>{1, -2}, Vector2d<int>{1, 2}};

            moves = get_moves_from_change_vectors(change_vectors);
            return moves;
        }

};