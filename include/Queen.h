#pragma once

class Queen : public Piece
{
    public:
        Queen(const char sign, const std::string& init_pos) : Piece{sign, init_pos}
        {}

        std::vector<Move> getAllowedMoves() const final
        {
            std::vector<Move> moves;
            return moves;
        }
};