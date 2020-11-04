#pragma once
#include "Pos.h"
#include "Move.h"
#include "Vector2d.h"
#include "Board.h"
#include "Color.h"
#include <string>
#include <vector>
#include <memory>
#include <array>

class Piece
{
    public:
        Piece() = default;

        Piece(const char init_sign, const std::string& init_pos) : sign{init_sign}, pos{init_pos}
        {
            color = islower(sign) ? Color::BLACK : Color::WHITE;
        }

        virtual ~Piece() = default;

        virtual std::vector<Move> get_allowed_moves() const = 0;
        
        void set_pos(const Position& new_pos)
        {
            pos = new_pos;
        }

        void set_board(std::shared_ptr<Board> init_board)
        {
            board = init_board;
        }

        Position get_pos() const
        {
            return pos;
        }

        std::string get_pos_as_string() const
        {
            return pos.get_string();
        }

        int get_color() const
        {
            return color;
        }

        char get_sign() const
        {
            return sign;
        }

        static void PrintMovesVector(std::vector<Move> moves, const std::string& header)
        {
            std::cout<<header<<"\n";

            for(const auto& move : moves)
                std::cout<<move<<"\n";
        }

    protected:

        bool piece_on_board(const Position& pos) const
        {
            return (pos.x >= 'a' && pos.x <= 'h' && pos.y >=1 && pos.y <= 8);
        }

        std::vector<Move> get_moves_from_change_vectors(std::vector<Vector2d<int>> change_vectors) const
        {
            std::vector<Move> moves;

            for(const auto& vector : change_vectors)
            {
                Position possible_pos = get_proposed_pos(vector);
                if(piece_on_board(possible_pos))
                    moves.push_back(Move{pos, possible_pos});
            }

            return moves;
        }

        Position get_proposed_pos(const Vector2d<int>& change_vector) const //think of it
        {
            int converted_x_pos = static_cast<int>(pos.x);
            return Position{static_cast<char>(converted_x_pos + change_vector.x), pos.y + change_vector.y};
        }

        bool piece_to_take_has_different_color(const Position& pos) const
        {
            return (board->get_color(pos) != color);
        }

        bool pieceToTakeHasSameColor(const Position& pos) const
        {
            return !piece_to_take_has_different_color(pos);
        }

        void delete_moves_finishing_on_ally_piece(std::vector<Move>& moves) const
        {
            for(unsigned i = 0; i < moves.size();)
            {
                Position nextPos = moves[i].next;

                if(board->is_not_empty(nextPos) && pieceToTakeHasSameColor(pos))
                    moves.erase(moves.begin() + i);

                else ++i;
            }
        }

    protected:
        int color;
        char sign;
        std::shared_ptr<Board> board;
        Position pos;
};