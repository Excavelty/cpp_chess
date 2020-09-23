#pragma once
#include <memory>
#include "Vector2d.h"

class Pawn : public Piece
{
    public:
        Pawn(const char sign, const std::string& init_pos) : Piece{sign, init_pos}
        {
            if(color == Color::BLACK)
                reverse_change_vectors();
        }

        std::vector<Move> get_allowed_moves() const final //remember about checking if on board etc
        {
            std::vector<Move> moves;
            
            Position left_take_pos = get_proposed_pos(left_take_change);
            Position right_take_pos = get_proposed_pos(right_take_change);
            Position first_step_pos = get_proposed_pos(first_step_change);
            Position second_step_pos = get_proposed_pos(second_step_change);

            if(allow_double_move)
            {

                if(board->is_empty(first_step_pos) && board->is_empty(second_step_pos))
                    moves.push_back(Move{pos, Position{pos.x, pos.y + 2}});
            }

            if(board->is_empty(first_step_pos))
                moves.push_back(Move{pos, Position{pos.x, pos.y + 1}});

            if(board->is_empty(left_take_pos) && board->get_color(left_take_pos) != color)
            {
                Move next_move{pos, Position{left_take_pos}};
                next_move.disallow_double_move();
                moves.push_back(next_move);
            }

            if(board->is_empty(right_take_pos) && board->get_color(right_take_pos) != color) //en passant later
            {
                Move next_move{pos, Position{right_take_pos}};
                next_move.disallow_double_move();
                moves.push_back(next_move);
            }

            return moves;
        }

        void disable_double_move()
        {
            allow_double_move = false;        
        }

        void set_en_passant_status(bool status)
        {
            allow_en_passant = status;
        }

    private:

        void reverse_change_vectors()
        {
            first_step_change = Vector2d<int>{0, -1};
            second_step_change = Vector2d<int>{0, -2};
            left_take_change = Vector2d<int>{1, -1};
            right_take_change = Vector2d<int>{1, 1};
            left_en_passant_change = Vector2d<int>{};
            right_en_passant_change = Vector2d<int>{};
        }

    private:
        Vector2d<int> first_step_change{0, 1};
        Vector2d<int> second_step_change{0, 2};
        Vector2d<int> left_take_change{-1, 1};
        Vector2d<int> right_take_change{1, 1};
        Vector2d<int> left_en_passant_change{-1, -1};
        Vector2d<int> right_en_passant_change{1, -1};
        bool allow_en_passant = false;
        bool allow_double_move = true;
};