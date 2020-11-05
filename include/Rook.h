#pragma once

#include "Piece.h"

class Rook : public Piece
{
    public:
        Rook(const char sign, const std::string& init_pos) : Piece{sign, init_pos}
        {}

        std::vector<Move> getAllowedMoves() const final
        {
            std::vector<Move> moves;
            return moves;
        }
};