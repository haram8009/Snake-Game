#pragma once
#include <ncurses.h>
#include "Board.hpp"
#include "BoardMap.hpp"
#include "Drawable.hpp"
#include "Apple.hpp"
#include "Poison.hpp"
#include "Empty.hpp"
// controler -> change model
// Apple이 random하게 나타나도록 함
#include <time.h>
#include <stdlib.h>
#include "Snake.hpp"
#include "Scoreboard.hpp"

class SnakeGame
{
  Board board;
  BoardMap boardmap;
  int stage;
  bool game_over;
  Apple *apple;
  Poison *poison;
  Snake snake;
  Scoreboard scoreboard;

  int growth;
  int poisoned;
  int curlength;
  int maxlength;

  void drawMap()
  {
    for (int i=0; i<21; i++){
       for (int j=0; j<42; j++){
         switch (boardmap.getMapVal(i,j)+'0') {
           case '0':
              break;
           case '1': // wall
              board.addAt(i,j,(boardmap.getMapVal(i,j))+'0'); // y, x, ch
              break;
           case '2': // immune wall
              board.addAt(i,j,(boardmap.getMapVal(i,j))+'0');
              break;
            default:
              board.addAt(i,j,(boardmap.getMapVal(i,j))+'0');
              break;
         }
       }
    }
    board.refresh();
    // 왜 안그려지냐~~~~!!!!!!
  }

  void createApple()
  {
      int y, x;
      board.getEmptyCoordinates(y,x);
      apple = new Apple(y, x);
      board.add(*apple);
  }
  void createPoison(){
    int y,x;
    board.getEmptyCoordinates(y,x);
    poison = new Poison(y, x);
    board.add(*poison);
  }

  void handleNextPiece(SnakePiece next)
  {
    if (curlength <= 3)
    {
      game_over = true;
    }
    if (apple != NULL && poison != NULL) {
      switch (board.getCharAt(next.getY(), next.getX())) {
        case 'A':
            eatApple();
            break;
        case 'P':
            eatPoisn();
            {
                int emptyRow = snake.tail().getY();
                int emptyCol = snake.tail().getX();
                board.add(Empty(emptyRow, emptyCol));
                snake.removePiece();
                emptyRow = snake.tail().getY();
                emptyCol = snake.tail().getX();
                board.add(Empty(emptyRow, emptyCol));
                snake.removePiece();
            }
            break;
        case ' ':
        {
            int emptyRow = snake.tail().getY();
            int emptyCol = snake.tail().getX();
            board.add(Empty(emptyRow, emptyCol));
            snake.removePiece();
            break;
        } // C++ : 케이스문안에서 그냥은 선언 못하고 이렇게 브라켓으 씌워줘야한다.
        case 'O': // body
        case '.': // wall
        case '#': // immune wall
            game_over = true;
            break;
        default:
            game_over = true;
            break;
      }
    }
    int y = snake.head().getY();
    int x = snake.head().getX();
    board.addAt(y,x,'O');

    board.add(next,'@'); // 새로운 머리
    snake.addPiece(next);
  }

  void eatApple()
  {
      delete apple;
      apple = NULL;
      growth += 1;
      curlength += 1;
      if(curlength>maxlength) maxlength=curlength;
      scoreboard.updateGrowth(growth);
      scoreboard.updateBest(curlength,maxlength);
  }
  void eatPoisn()
  {
      delete poison;
      poison = NULL;
      poisoned += 1;
      curlength -= 1;
      scoreboard.updatePoisoned(poisoned);
      scoreboard.updateBest(curlength,maxlength);
  }

public:
    SnakeGame(int height, int width, int stage, int speed=300)
    {
        board = Board(height, width, speed);
        this->stage = stage;
        boardmap = BoardMap(stage);
        int sb_row = board.getStartRow() + height;
        int sb_col = board.getStartCol();
        scoreboard = Scoreboard(width, sb_row, sb_col);
        initialize();
    }
    ~SnakeGame()
    {
        delete apple;
        delete poison;
    }

    void initialize()
    {
      apple = NULL;
      poison = NULL;

      board.initialize();
      drawMap(); // 맵


      growth = 0;
      poison = 0;
      curlength = 4;
      maxlength = 4;
      scoreboard.initialize(growth, poisoned, curlength, maxlength);
      game_over = false;
      srand(time(NULL));
      snake.setDirection(down); // 디폴트는 다운

      snake.addPiece(SnakePiece(1,1));
      handleNextPiece(snake.nextHead());
      handleNextPiece(snake.nextHead());
      snake.setDirection(right);
      handleNextPiece(snake.nextHead());

      if(apple == NULL)
      {
          createApple();
      }
      if(poison == NULL)
      {
          createPoison();
      }
    }

    void processInput()
    {
        chtype input = board.getInput();
        switch(input)
        {
            case KEY_UP:
            case 'w':
            case 'W':
                snake.setDirection(up);
                break;
            case KEY_DOWN:
            case 's':
            case 'S':
                snake.setDirection(down);
                break;
            case KEY_RIGHT:
            case 'd':
            case 'D':
                snake.setDirection(right);
                break;
            case KEY_LEFT:
            case 'a':
            case 'A':
                snake.setDirection(left);
                break;

            case 'p':
                board.setTimeout(-1); // 정지
                while(board.getInput()!='p')
                    ; // 다시 p를 누를때까지 루프를 벗어나지 않음 == 정지상태 유지
                board.setTimeout(300);
                break;
            default:
                break;
        }
    }

    void updateState()
    {
        handleNextPiece(snake.nextHead());

        if(apple == NULL)
        {
            createApple();
        }
        if(poison == NULL)
        {
            createPoison();
        }
    }

    void redraw()
    {
        board.refresh();
        scoreboard.refresh();
    }

    bool isOver()
    {
        return game_over;
    }

    int getGrowth()
    {
        return growth;
    }
    int getPoisoned()
    {
        return poisoned;
    }
    int getCurlength()
    {
        return curlength;
    }
    int getMaxlength()
    {
        return maxlength;
    }
};
