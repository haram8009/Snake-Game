#pragma once
#include <ncurses.h>
#include "Drawable.hpp"
#include <queue>

enum Direction
{
    up = -1,
    down = 1,
    left = -2,
    right = 2
};

class SnakePiece : public Drawable
{
public:
    SnakePiece()
    {
        this->x = this->y = 0;
        this->icon = '#';
    }
    SnakePiece(int y, int x)
    {
        this->x = x;
        this->y = y;
        this->icon = '#';
    }
};

class Snake
{
    std::queue<SnakePiece> prev_pieces;
    Direction cur_direction;

public:
    Snake()
    {
      cur_direction = down; // 초기값을 그냥 douwn으로..
    }
    void addPiece(SnakePiece piece)
    {
      prev_pieces.push(piece);
    }
    void removePiece()
    {
      prev_pieces.pop();
    }
    SnakePiece tail()
    {
      return prev_pieces.front();
    }
    SnakePiece head()
    {
      return prev_pieces.back();
    }

    Direction getDirectioin(Direction d)
    {
      if (cur_direction + d != 0)
          return cur_direction;
      // 이건 게임 오버가 아니라 '아무것도 안하기' !!! 게임오버하도록 바꿔줘야함
    }

    void setDirection(Direction d)
    {
      cur_direction = d;
    }

    SnakePiece nextHead(){
      int row = head().getX();
      int col = head().getY();

      switch (cur_direction) {
        case down :
          row++;
          break;
        case up :
          row--;
          break;
        case left :
          col-- ;
          break;
        case right :
          col++;
          break;
      }
      return SnakePiece(row,col);
    }
};

/*
스네이크가 움직이는 과정 : 영상 참고
https://youtu.be/l0XRPnKwz30

Direction:
down : row+1,col
up : row-1 , col
left : row, col-1
right : row, col+1


States :
  initialization
  main

initialization state steps:
1. 뱀 조각을 만들고 위치를 할당
2. "Draw" 스네이크 조각
3. 스네이크 조각을 큐에 추가
4. 반복

main state steps:
1. 머리의 다음 위치를 구한다 (current head + Direction)
2. 만약 다음 위치가 ' '라면, 큐에서 뱀조각 pop 한 뒤 위치에 ' '추가
3. 새로운 뱀 조각 만들고 new cordinates(좌표)에 할당
4. "Draw" snake piece
5. add SnakePiece to queue

*/
