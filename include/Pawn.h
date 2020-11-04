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

            add_straight_moves_to_allowed(moves);
            add_take_moves_to_allowed(moves);

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
            left_take_change = Vector2d<int>{1, 1};
            right_take_change = Vector2d<int>{-1, 1};
            left_en_passant_change = Vector2d<int>{1, 1};
            right_en_passant_change = Vector2d<int>{-1, 1};
        }

        void add_straight_moves_to_allowed(std::vector<Move>& moves) const
        {
            
            Position first_step_pos = get_proposed_pos(first_step_change);
            Position second_step_pos = get_proposed_pos(second_step_change);

            if(allow_double_move && board->is_empty(first_step_pos) && board->is_empty(second_step_pos))
            {
                add_single_pawn_move_to_allowed(moves, first_step_pos);
            }

            if(board->is_empty(first_step_pos))
            {
                add_single_pawn_move_to_allowed(moves, second_step_pos);
            }
        }

        void add_take_moves_to_allowed(std::vector<Move>& moves) const
        {
            Position left_take_pos = get_proposed_pos(left_take_change);
            Position right_take_pos = get_proposed_pos(right_take_change);

            if(board->is_not_empty(left_take_pos) && piece_to_take_has_different_color(left_take_pos))
            {
                add_single_pawn_move_to_allowed(moves, left_take_pos);
            }

            if(board->is_not_empty(right_take_pos) && piece_to_take_has_different_color(right_take_pos)) //en passant later
            {
                add_single_pawn_move_to_allowed(moves, right_take_pos);
            }

        }

        void add_single_pawn_move_to_allowed(std::vector<Move>& moves, const Position& next_pos) const
        {
                Move next_move{pos, next_pos};
                next_move.disallow_double_move();
                moves.push_back(next_move);
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