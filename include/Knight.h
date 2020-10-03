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

            auto iterator = moves.begin();
            while(iterator != moves.end())
            {
                int counter = iterator - moves.begin();
                bool field_empty = board->is_empty(moves[counter].next);
                bool piece_to_take = false;

                if(!field_empty)
                {
                    piece_to_take = board->get_color(moves[counter].next) != color;   
                    if(piece_to_take)
                        moves[counter].set_take_flag();
                }

                if(!field_empty && !piece_to_take)
                    moves.erase(moves.begin() + counter);

                ++iterator;
            }

            return moves;
        }

    private:
};
