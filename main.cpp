#include <iostream>
#include <ncurses.h>
#include "src/Board.hpp"
#include "src/SnakeGame.hpp"
#include "src/Drawable.hpp"

#define BOARD_DIM 21
#define BOARD_ROWS BOARD_DIM * 2
#define BOARD_COLS BOARD_DIM

int main()
{
    initscr();
    refresh();
    noecho(); // 키를 눌러도 화면에 띄우지 않음 (processInput이 키입력을 받으면서 화면에 띄우기때문)
    curs_set(0); // 커서 없애기

    int stage=2;

    

    SnakeGame game(BOARD_COLS, BOARD_ROWS, stage, 300);

    while(!game.isOver())
    {
        // 1: get input from user
        game.processInput();

        // 2: update game state
        game.updateState();

        // 3: redraw display
        game.redraw();

        // 4: go to 1, unless game over
    }

    getch();
    endwin();

    std::cout << "GameOver" << std::endl;

    return 0;
}
