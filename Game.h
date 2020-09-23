#pragma once
#include <iostream>
#include "Board.h"
#include "pieces_header.h"
#include "NoPieceFoundException.h"
#include <vector>
#include <memory>
#include <algorithm>

class Game
{
    public:

        Game() : board{new Board}
        {
            init_pawns();
            init_rooks();
            init_kings();
            init_knights();
            init_queens();
            init_bishops();
            for(const auto& piece : pieces)
            {
                std::cout<<piece->get_sign()<<" "<<piece->get_pos()<<"\n";
            }
        }

        void loop()
        {
            std::string move_str;
            while(true)
            {
                std::cin>>move_str;
                if(move_str == "exit")
                {
                    std::cout<<"Game was finished!"<<"\n";
                    break;
                }
                
                else 
                {
                    Position current_pos{move_str.substr(0, 2)};
                    Position next_pos{move_str.substr(2, 2)};

                    Move move{current_pos, next_pos};
                    auto piece_iterator = std::find_if(pieces.begin(), pieces.end(), 
                      [&current_pos](const auto& el) { return el->get_pos() == current_pos; });

                    try
                    {
                        if(piece_iterator == pieces.end())
                            throw NoPieceFoundException{};

                        std::shared_ptr<Piece> piece = pieces[piece_iterator - pieces.begin()];    
                        std::vector<Move> allowed_moves = piece->get_allowed_moves();
                        for(const auto& move : allowed_moves)
                            std::cout<<move<<"\n";
                    }

                    catch(const NoPieceFoundException& exception)
                    {
                        std::cout<<exception.what()<<"\n";
                        std::cout<<current_pos;
                    }

                    if(board->is_move_allowed(move))
                        board->move(move.previous, move.next);
                    board->print();
                }
            }
        }

    private:
        void init_kings()
        {
            std::shared_ptr<King> black_king{new King{'k', "e8"}};
            std::shared_ptr<King> white_king{new King{'K', "e1"}};
            pieces.push_back(black_king);
            pieces.push_back(white_king);
        }

        void init_pawns()
        {
            for(int i = 0; i < size; ++i)
            {
                char col_sign = 'a' + i;
                std::shared_ptr<Pawn> black_pawn{new Pawn{'p', std::string{col_sign} + std::to_string(7)}};
                std::shared_ptr<Pawn> white_pawn{new Pawn{'P', std::string{col_sign} + std::to_string(2)}};
                pieces.push_back(black_pawn);
                pieces.push_back(white_pawn);
            }
        }

        void init_rooks()
        {
            const std::string black_pos[] = {"a8", "h8"};
            const std::string white_pos[] = {"a1", "h1"};

            for(int i = 0; i < 2; ++i)
            {
                std::shared_ptr<Rook> black_rook{new Rook{'r', black_pos[i]}};
                std::shared_ptr<Rook> white_rook{new Rook{'R', white_pos[i]}};
                pieces.push_back(black_rook);
                pieces.push_back(white_rook);
            }
        }

        void init_bishops()
        {
            const std::string black_pos[] = {"c8", "f8"};
            const std::string white_pos[] = {"c1", "f1"};

            for(int i = 0; i < 2; ++i)
            {
                std::shared_ptr<Bishop> black_bishop{new Bishop{'b', black_pos[i]}};
                std::shared_ptr<Bishop> white_bishop{new Bishop{'B', white_pos[i]}};
                pieces.push_back(black_bishop);
                pieces.push_back(white_bishop);
            }
        }

        void init_knights()
        {
            const std::string black_pos[] = {"b8", "g8"};
            const std::string white_pos[] = {"b1", "g1"};

             for(int i = 0; i < 2; ++i)
            {
                std::shared_ptr<Knight> black_knight{new Knight{'n', black_pos[i]}};
                std::shared_ptr<Knight> white_knight{new Knight{'N', white_pos[i]}};
                pieces.push_back(black_knight);
                pieces.push_back(white_knight);
            }
        }

        void init_queens()
        {
            std::shared_ptr<Queen> black_queen{new Queen{'q', "d8"}};
            std::shared_ptr<Queen> white_queen{new Queen{'Q', "d1"}};
            pieces.push_back(black_queen);
            pieces.push_back(white_queen);
        }

    private:
        const int size = 8;
        std::shared_ptr<Board> board;
        std::vector<std::shared_ptr<Piece>> pieces;
};