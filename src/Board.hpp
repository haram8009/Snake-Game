#pragma once
#include <ncurses.h>
#include "Drawable.hpp"

class Board
{
public:
    Board()
    {
        construct(0, 0, 300);
    }

    Board(int height, int width, int speed)
    {
        construct(height, width, speed);
    }

    void initialize()
    {
        clear();
        refresh();
    }

    // 테두리 그리기
    void addBorder()
    {
        box(board_win, 0, 0);
    }

    void add(Drawable drawable)
    {
        addAt(drawable.getY(), drawable.getX(), drawable.getIcon());
    }

    void addAt(int y, int x, chtype ch)
    {
        mvwaddch(board_win, y, x , ch);
    }

    chtype getInput()
    {
        return wgetch(board_win);
    }

    void getEmptyCoordinates(int &y, int &x)
    {
        while((mvwinch(board_win, y = rand() % height, x = rand() % width)) != ' ' );
        // y = rand() % height == 랜덤한 넘버 0 ~ height
        // ' '를 찾을때까지 x,y를 찾음
    }

    chtype getCharAt(int y, int x)
    {
        return mvwinch(board_win, y, x);
    }

    // 윈도우 초기화후 테두리 그리기
    void clear()
    {
        wclear(board_win);
        addBorder();
    }

    void refresh()
    {
        wrefresh(board_win);
    }

    void setTimeout(int timeout)
    {
        wtimeout(board_win, timeout);
    }

    int getStartRow()
    {
        return start_row;
    }
    int getStartCol()
    {
        return start_col;
    }
private:
    WINDOW *board_win;
    int height, width, start_row, start_col;

    void construct(int height, int width, int speed)
    {
        int xMax, yMax;
        getmaxyx(stdscr, yMax, xMax);
        this->height = height;
        this->width = width;

        start_row = (yMax/2)-(height /2);
        start_col = (xMax/2)-(width/2);

        board_win = newwin( height, width, start_row, start_col);
        setTimeout(speed); // speed 마다 업데이트 (게임 진행 속도 조절)

        keypad(board_win, true); // 방향키 받아오기 가능
    }
};
