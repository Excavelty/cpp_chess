#pragma once
#include <iostream>
#include "Board.h"
#include "pieces_header.h"
#include "NoPieceFoundException.h"
#include "NoMoveAllowed.h"
#include <vector>
#include <memory>
#include <algorithm>

class Game
{
    public:

        Game() : board{new Board}
        {
            initPawns();
            initRooks();
            initKings();
            initKnights();
            initQueens();
            initBishops();

            setBoardForPieces();
        }

        void loop()
        {
            std::string move_str;
            while(true)
            {
                std::cin>>move_str;
                if(checkIfShouldExit(move_str))
                {
                    printOnExitMessage();
                    break;
                }
                
                else proceedMove(move_str);
            }
        }

    private:
        void initKings()
        {
            std::shared_ptr<King> blackKing{new King{'k', "e8"}};
            std::shared_ptr<King> whiteKing{new King{'K', "e1"}};
            pieces.push_back(blackKing);
            pieces.push_back(whiteKing);
        }

        void initPawns()
        {
            for(int i = 0; i < size; ++i)
            {
                char colSign = 'a' + i;
                std::shared_ptr<Pawn> blackPawn{new Pawn{'p', std::string{colSign} + std::to_string(7)}};
                std::shared_ptr<Pawn> whitePawn{new Pawn{'P', std::string{colSign} + std::to_string(2)}};
                pieces.push_back(blackPawn);
                pieces.push_back(whitePawn);
            }
        }

        void initRooks()
        {
            const std::string blackPos[] = {"a8", "h8"};
            const std::string whitePos[] = {"a1", "h1"};

            for(int i = 0; i < 2; ++i)
            {
                std::shared_ptr<Rook> blackRook{new Rook{'r', blackPos[i]}};
                std::shared_ptr<Rook> whiteRook{new Rook{'R', whitePos[i]}};
                pieces.push_back(blackRook);
                pieces.push_back(whiteRook);
            }
        }

        void initBishops()
        {
            const std::string blackPos[] = {"c8", "f8"};
            const std::string whitePos[] = {"c1", "f1"};

            for(int i = 0; i < 2; ++i)
            {
                std::shared_ptr<Bishop> blackBishop{new Bishop{'b', blackPos[i]}};
                std::shared_ptr<Bishop> whiteBishop{new Bishop{'B', whitePos[i]}};
                pieces.push_back(blackBishop);
                pieces.push_back(whiteBishop);
            }
        }

        void initKnights()
        {
            const std::string blackPos[] = {"b8", "g8"};
            const std::string whitePos[] = {"b1", "g1"};

             for(int i = 0; i < 2; ++i)
            {
                std::shared_ptr<Knight> blackKnight{new Knight{'n', blackPos[i]}};
                std::shared_ptr<Knight> whiteKnight{new Knight{'N', whitePos[i]}};
                pieces.push_back(blackKnight);
                pieces.push_back(whiteKnight);
            }
        }

        void initQueens()
        {
            std::shared_ptr<Queen> blackQueen{new Queen{'q', "d8"}};
            std::shared_ptr<Queen> whiteQueen{new Queen{'Q', "d1"}};
            pieces.push_back(blackQueen);
            pieces.push_back(whiteQueen);
        }

        void removeTakenPiece(const Position& pos)
        {
            auto iter = std::find_if(pieces.begin(), pieces.end(), 
              [&pos] (const auto& piece) { return piece->getPos() == pos; });
            
            pieces.erase(iter);
            board->cleanField(pos);
        }

        void setBoardForPieces()
        {
            for(auto& piece : pieces)
                piece->setBoard(board);
        }

        void printPieces() const
        {
            for(const auto& piece : pieces) //important
            {
                std::cout<<piece->getSign()<<" "<<piece->getPos()<<" "<<piece->getColor()<<"\n";
            }
        }

        bool checkIfMoveAllowed(std::vector<std::shared_ptr<Piece>>::iterator piece_iterator, const Move& move, 
                                   std::shared_ptr<Piece> piece)
        {    
            std::vector<Move> allowedMoves = piece->getAllowedMoves();
            auto moveIterator = std::find(allowedMoves.begin(), allowedMoves.end(), move);

            if(moveIterator == allowedMoves.end())
                throw NoMoveAllowedException{"This move is not allowed!"};

            Piece::PrintMovesVector(allowedMoves, "Possible moves: ");
            return true;
        }

        bool checkIfShouldExit(const std::string& str)
        {
            return (str == "exit");
        }

        void proceedMove(const std::string& moveStr)
        {
             Position currentPos{moveStr.substr(0, 2)};
             Move move = Move::GetMoveFromString(moveStr);

            auto pieceIterator = std::find_if(pieces.begin(), pieces.end(), 
                [&currentPos](const auto& el) { return el->getPos() == currentPos; });

            try
            {
                tryToFinalizeMove(pieceIterator, move);
            }

            catch(const NoPieceFoundException& exception)
            {
                std::cout<<exception.what()<<"\n";
                std::cout<<currentPos;
            }

            catch(const NoMoveAllowedException& exception)
            {
                std::cout<<exception.what()<<"\n";
            }
        }

        void tryToFinalizeMove(std::vector<std::shared_ptr<Piece>>::iterator piece_iterator, const Move& move)
        {
            if(piece_iterator == pieces.end())
                throw NoPieceFoundException{};

            std::shared_ptr<Piece> piece = pieces[piece_iterator - pieces.begin()];

            if(checkIfMoveAllowed(piece_iterator, move, piece))
                executeMoveWithPiece(piece, move);
        }

        void executeMoveWithPiece(std::shared_ptr<Piece> piece, const Move& move)
        {
            if(move.isTake())
                removeTakenPiece(move.next);

            piece->setPos(move.next);
            board->move(move.previous, move.next);
                                    
            //print_pieces();
            board->print();
        }

        void printOnExitMessage()
        {
            std::cout<<"Game was finished!"<<"\n";
        }

    private:
        const int size = 8;
        std::shared_ptr<Board> board;
        std::vector<std::shared_ptr<Piece>> pieces;
};