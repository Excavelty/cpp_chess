#pragma once

#include "Piece.h"

class Bishop : public Piece
{
    public:
        Bishop(const char sign, const std::string& initPos) : Piece{sign, initPos}
        {}

        std::vector<Move> getAllowedMoves() const override final
        {
            std::vector<Move> moves;
            return moves;
        }
};