#pragme once
#include <iostream>
#include "Board.h"

class Game
{
    public:
        void loop()
        {
            Board board;
            std::string move_str;
            std::cin>>move_str;
            
             while(move_str != exit)
             {
                 board.move(move_str.split(0, 2), move_str.split(2, 2)); //thinks of it 
                 std::cin>>move_str;
             }
        }

    private:
};