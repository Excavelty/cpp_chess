#pragma once

#include "Piece.h"

class King : public Piece
{
    public:
        King(const char sign, const std::string& init_pos) : Piece{sign, init_pos}
        {}

        std::vector<Move> getAllowedMoves() const final
        {
            std::vector<Move> moves;
            std::vector<Vector2d<int>> changeVectors 
            = {Vector2d<int>{-1, -1}, Vector2d<int>{-1, 1}, Vector2d<int>{-1, 0}, Vector2d<int>{1, 0}, 
               Vector2d<int>{0, -1}, Vector2d<int>{0, 1}, Vector2d<int>{1, -1}, Vector2d<int>{1, 1}};

            moves = getMovesFromChangeVectors(changeVectors);
            return moves;
        }

    private:

};