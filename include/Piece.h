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

        virtual std::vector<Move> getAllowedMoves() const = 0;
        
        void setPos(const Position& new_pos)
        {
            pos = new_pos;
        }

        void setBoard(std::shared_ptr<Board> init_board)
        {
            board = init_board;
        }

        Position getPos() const
        {
            return pos;
        }

        std::string getPosAsString() const
        {
            return pos.getString();
        }

        int getColor() const
        {
            return color;
        }

        char getSign() const
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

        bool pieceOnBoard(const Position& pos) const
        {
            return (pos.x >= 'a' && pos.x <= 'h' && pos.y >=1 && pos.y <= 8);
        }

        std::vector<Move> getMovesFromChangeVectors(std::vector<Vector2d<int>> changeVectors) const
        {
            std::vector<Move> moves;

            for(const auto& vector : changeVectors)
            {
                Position possiblePos = getProposedPos(vector);
                if(pieceOnBoard(possiblePos))
                    moves.push_back(Move{pos, possiblePos});
            }

            return moves;
        }

        Position getProposedPos(const Vector2d<int>& changeVector) const //think of it
        {
            int convertedXPos = static_cast<int>(pos.x);
            return Position{static_cast<char>(convertedXPos + changeVector.x), pos.y + changeVector.y};
        }

        bool pieceToTakeHasDifferentColor(const Position& pos) const
        {
            return (board->getColor(pos) != color);
        }

        bool pieceToTakeHasSameColor(const Position& pos) const
        {
            return !pieceToTakeHasDifferentColor(pos);
        }

        void deleteMovesFinishingOnAllyPiece(std::vector<Move>& moves) const
        {
            for(unsigned i = 0; i < moves.size();)
            {
                Position nextPos = moves[i].next;

                if(board->isNotEmpty(nextPos) && pieceToTakeHasSameColor(pos))
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