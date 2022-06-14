#pragma once
#include <ncurses.h>
#include "Board.hpp"
#include "Drawable.hpp"
#include "Apple.hpp"
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
  Snake snake;
  Scoreboard scoreboard;
  int score;

  void createApple()
  {
      int y, x;
      board.getEmptyCoordinates(y,x);
      apple = new Apple(y, x);
      board.add(*apple);
  }

  void handleNextPiece(SnakePiece next)
  {
    if (apple != NULL) {
      switch (board.getCharAt(next.getY(), next.getX())) {
        case 'A':
            eatApple();
            break;
        case ' ':
        {
            int emptyRow = snake.tail().getY();
            int emptyCol = snake.tail().getX();
            board.add(Empty(emptyRow, emptyCol));
            snake.removePiece();
            break;
        } // 씨플플은 케이스문안에서 그냥은 선언 못하고 이렇게 브라켓으 씌워줘야한대
        default: // 공백도 아니고 애플도 아니면 게임 오버지~ 라는 뜻 우리는 이걸 고쳐야한다.
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
      score += 100; //// 스코어가 아니라 growth 아이템을 먹은 횟수가 되겠지..수정필요
      scoreboard.updateScore(score);
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
    }

    void initialize()
    {
      apple = NULL;
      board.initialize();

      score = 0;
      scoreboard.initialize(score);

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
                board.setTimeout(-1);
                while(board.getInput()!='p')
                    ; // 다시 p를 누를때까지 루프를 벗어나지 않음 == 정지상태
                board.setTimeout(1000);
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

    int getScore()
    {
        return score;
    }
};
