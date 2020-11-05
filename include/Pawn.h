#pragma once
#include <memory>
#include "Vector2d.h"

class Pawn : public Piece
{
    public:
        Pawn(const char sign, const std::string& initPos) : Piece{sign, initPos}
        {
            if(color == Color::BLACK)
                reverseChangeVectors();
        }

        std::vector<Move> getAllowedMoves() const override final //remember about checking if on board etc
        {
            std::vector<Move> moves;

            addStraightMovesToAllowed(moves);
            addTakeMovesToAllowed(moves);

            return moves;
        }

        void disableDoubleMove()
        {
            allowDoubleMove = false;        
        }

        void setEnPassantStatus(bool status)
        {
            allowEnPassant = status;
        }

    private:

        void reverseChangeVectors()
        {
            firstStepChange = Vector2d<int>{0, -1};
            secondStepChange = Vector2d<int>{0, -2};
            leftTakeChange = Vector2d<int>{1, 1};
            rightTakeChange = Vector2d<int>{-1, 1};
            leftEnPassantChange = Vector2d<int>{1, 1};
            rightEnPassantChange = Vector2d<int>{-1, 1};
        }

        void addStraightMovesToAllowed(std::vector<Move>& moves) const
        {
            
            Position firstStepPos = getProposedPos(firstStepChange);
            Position secondStepPos = getProposedPos(secondStepChange);

            if(allowDoubleMove && board->isEmpty(firstStepPos) && board->isEmpty(secondStepPos))
            {
                addSinglePawnMoveToAllowed(moves, firstStepPos);
            }

            if(board->isEmpty(firstStepPos))
            {
                addSinglePawnMoveToAllowed(moves, secondStepPos);
            }
        }

        void addTakeMovesToAllowed(std::vector<Move>& moves) const
        {
            Position leftTakePos = getProposedPos(leftTakeChange);
            Position rightTakePos = getProposedPos(rightTakeChange);

            if(board->isNotEmpty(leftTakePos) && pieceToTakeHasDifferentColor(leftTakePos))
            {
                addSinglePawnMoveToAllowed(moves, leftTakePos);
            }

            if(board->isNotEmpty(rightTakePos) && pieceToTakeHasDifferentColor(rightTakePos)) //en passant later
            {
                addSinglePawnMoveToAllowed(moves, rightTakePos);
            }

        }

        void addSinglePawnMoveToAllowed(std::vector<Move>& moves, const Position& nextPos) const
        {
                Move nextMove{pos, nextPos};
                nextMove.disallowDoubleMove();
                moves.push_back(nextMove);
        }

    private:
        Vector2d<int> firstStepChange{0, 1};
        Vector2d<int> secondStepChange{0, 2};
        Vector2d<int> leftTakeChange{-1, 1};
        Vector2d<int> rightTakeChange{1, 1};
        Vector2d<int> leftEnPassantChange{-1, -1};
        Vector2d<int> rightEnPassantChange{1, -1};
        bool allowEnPassant = false;
        bool allowDoubleMove = true;
};