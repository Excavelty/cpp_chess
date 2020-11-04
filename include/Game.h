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
            init_pawns();
            init_rooks();
            init_kings();
            init_knights();
            init_queens();
            init_bishops();

            set_board_for_pieces();
        }

        void loop()
        {
            std::string move_str;
            while(true)
            {
                std::cin>>move_str;
                if(check_if_should_exit(move_str))
                {
                    print_on_exit_message();
                    break;
                }
                
                else proceed_move(move_str);
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

        void remove_taken_piece(const Position& pos)
        {
            auto iter = std::find_if(pieces.begin(), pieces.end(), 
              [&pos] (const auto& piece) { return piece->get_pos() == pos; });
            
            pieces.erase(iter);
            board->clean_field(pos);
        }

        void set_board_for_pieces()
        {
            for(auto& piece : pieces)
                piece->set_board(board);
        }

        void print_pieces() const
        {
            for(const auto& piece : pieces) //important
            {
                std::cout<<piece->get_sign()<<" "<<piece->get_pos()<<" "<<piece->get_color()<<"\n";
            }
        }

        bool check_if_move_allowed(std::vector<std::shared_ptr<Piece>>::iterator piece_iterator, const Move& move, 
                                   std::shared_ptr<Piece> piece)
        {    
            std::vector<Move> allowed_moves = piece->get_allowed_moves();
            auto move_iterator = std::find(allowed_moves.begin(), allowed_moves.end(), move);

            if(move_iterator == allowed_moves.end())
                throw NoMoveAllowedException{"This move is not allowed!"};

            Piece::PrintMovesVector(allowed_moves, "Possible moves: ");
            return true;
        }

        bool check_if_should_exit(const std::string& str)
        {
            return (str == "exit");
        }

        void proceed_move(const std::string& move_str)
        {
             Position current_pos{move_str.substr(0, 2)};
             Move move = Move::GetMoveFromString(move_str);

            auto piece_iterator = std::find_if(pieces.begin(), pieces.end(), 
                [&current_pos](const auto& el) { return el->get_pos() == current_pos; });

            try
            {
                try_to_finalize_move(piece_iterator, move);
            }

            catch(const NoPieceFoundException& exception)
            {
                std::cout<<exception.what()<<"\n";
                std::cout<<current_pos;
            }

            catch(const NoMoveAllowedException& exception)
            {
                std::cout<<exception.what()<<"\n";
            }
        }

        void try_to_finalize_move(std::vector<std::shared_ptr<Piece>>::iterator piece_iterator, const Move& move)
        {
            if(piece_iterator == pieces.end())
                throw NoPieceFoundException{};

            std::shared_ptr<Piece> piece = pieces[piece_iterator - pieces.begin()];

            if(check_if_move_allowed(piece_iterator, move, piece))
                execute_move_with_piece(piece, move);
        }

        void execute_move_with_piece(std::shared_ptr<Piece> piece, const Move& move)
        {
            if(move.is_take())
                remove_taken_piece(move.next);

            piece->set_pos(move.next);
            board->move(move.previous, move.next);
                                    
            //print_pieces();
            board->print();
        }

        void print_on_exit_message()
        {
            std::cout<<"Game was finished!"<<"\n";
        }

    private:
        const int size = 8;
        std::shared_ptr<Board> board;
        std::vector<std::shared_ptr<Piece>> pieces;
};