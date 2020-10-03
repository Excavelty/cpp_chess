#pragma once

class Queen : public Piece
{
    public:
        Queen(const char sign, const std::string& init_pos) : Piece{sign, init_pos}
        {}

        std::vector<Move> get_allowed_moves() const final
        {
            std::vector<Move> moves;
            return moves;
        }
};