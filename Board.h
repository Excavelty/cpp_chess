#pragma once
#include <iostream>
#include <array>

class Board
{
    public:
        Board()
        {
            init_board();
        }

        void print() const
        {
            for(int j = num - 1; j >= 0; --j)
            {
                for(int i = 0; i < num; ++i)
                    std::cout<<fields[i][j];
                std::cout<<"\n";
            }
        }

        char get(int first, int second) const
        {
            return fields[first][second];
        } // use counting from 0

        void set(const std::string& previous, const std::string& next)
        {
            char p_first = previous[0];
            int p_second = previous[1] - '0';
            char first = next[0];
            int second = next[1] - '0';

            fields[first - 'a'][second - 1] = fields[p_first - 'a'][p_second - 1];
            fields[p_first - 'a'][p_second - 1] = '-';
        }

        void move(const std::string& first, const std::string& second)
        {
            set(first, second);
        }

        std::array<std::array<char, 8>, 8> get_board() 
        {
            return fields;
        }

    private:
        void init_board()
        {
            for(int i = 0; i < num; ++i)
                for(int j = 0; j < num; ++j)
                    fields[i][j] = '-';

            fields[0][0] = fields[7][0] = 'R';
            fields[1][0] = fields[6][0] = 'N';
            fields[2][0] = fields[5][0] = 'B';
            fields[3][0] = 'Q';
            fields[4][0] = 'K';

            fields[0][7] = fields[7][7] = 'r';
            fields[1][7] = fields[6][7] = 'n';
            fields[2][7] = fields[5][7] = 'b';
            fields[3][7] = 'q';
            fields[4][7] = 'k';

            for(int i = 0; i < num; ++i)
            {
                fields[i][1] = 'P';
                fields[i][6] = 'p';
            }
        }
    
    private:
        const int num = 8; //responsible for rows and cols
        std::array<std::array<char, 8>, 8> fields;
};