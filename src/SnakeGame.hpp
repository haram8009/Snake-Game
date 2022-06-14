#pragma once
#include <ncurses.h>
#include "Board.hpp"
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
  bool game_over;
  Apple *apple;
  Poison *poison;
  Snake snake;
  Scoreboard scoreboard;

  int growth;
  int poisoned;
  int curlength;
  int maxlength;

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
        } // 씨플플은 케이스문안에서 그냥은 선언 못하고 이렇게 브라켓으 씌워줘야한대
        default: // 공백도 아니고 애플도 아니고 포이즌도 아니면 게임 오버~ 라는 뜻
            game_over = true;
            break;
      }
    }
    board.add(next);
    snake.addPiece(next);
  }

  void eatApple()
  {
      delete apple;
      apple = NULL;
      growth += 1;
      curlength += 1;
      if(curlength>maxlength) maxlength=curlength;
      scoreboard.updateGrowth(growth); // update growth 로 함수를 바꿔야..?
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
    SnakeGame(int height, int width, int speed=300)
    {
        board = Board(height, width, speed);
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

      growth = 0;
      poison = 0;
      curlength = 4;
      maxlength = 4;
      scoreboard.initialize(growth, poisoned, curlength, maxlength); // 여기도 수정 필요 ~~ ( length~~~ )

      game_over = false;
      srand(time(NULL));
      snake.setDirection(down); //지금 디폴트는 다운

      handleNextPiece(SnakePiece(1,1));
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
                board.setTimeout(300); // 이거 이렇게 하면 안돼고 speed 값을 가져와야하는데...
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
