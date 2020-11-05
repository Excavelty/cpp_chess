#pragma once
#include "Piece.h"

class Knight : public Piece //work on knight validation
{
    public:
        Knight(const char sign, const std::string& init_pos) : Piece{sign, init_pos}
        {}

        std::vector<Move> getAllowedMoves() const final
        {
            std::vector<Move> moves;
            std::vector<Vector2d<int>> changeVectors = 
                {Vector2d<int>{-2, -1}, Vector2d<int>{-2, 1}, Vector2d<int>{2, -1}, Vector2d<int>{2, 1}, 
                Vector2d<int>{-1, -2}, Vector2d<int>{-1, 2}, Vector2d<int>{1, -2}, Vector2d<int>{1, 2}};

            moves = getMovesFromChangeVectors(changeVectors);
            deleteMovesFinishingOnAllyPiece(moves);

            return moves;
        }

    private:
};
