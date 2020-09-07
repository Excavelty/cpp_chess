#include "Board.h"

int main()
{
    //Game game;
    Board board;
    board.move("e2", "e4");
    board.move("e7", "e5");
    
    board.print();
    //game.loop();
    return 0;
}