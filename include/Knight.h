#pragma once
#include "Piece.h"

class Knight : public Piece //work on knight validation
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
            delete_moves_finishing_on_ally_piece(moves);

            return moves;
        }

    private:
};
