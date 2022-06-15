#pragma once
#include <ncurses.h>
#include <fstream>
#include <string.h>
#include "Drawable.hpp"
#include "Board.hpp"

class BoardMap
{
    int **SnakeMap;
    void construct(int stage)
    {
      char map[9];
      SnakeMap = new int*[21];
      for(int i=0; i<21; i++){
        SnakeMap[i] = new int[42];
      }
      char c;
      switch (stage) {
        // case 0: //시작화면?
        case 1:
            strcpy(map, "map1.txt");
            break;
        case 2:
            strcpy(map, "map2.txt");
            break;
        case 3:
            strcpy(map, "map3.txt");
            break;
        case 4:
            strcpy(map, "map4.txt");
            break;
        // case 999: //게임오버화면?
      }
      std::ifstream file(map);
      if(file.is_open()){
         for (int i=0; i<21; i++){
            for (int j=0; j<42; j++){
              file.get(c);
              while( c <= '0' || c >= '9' ) file.get(c);
              SnakeMap[i][j] = c-'0';
            }
         }
      }
      file.close(); // 열었던 파일을 닫는다.
    }

public:
    BoardMap()
    {
        construct(1);
    }
    BoardMap(int stage)
    {
        construct(stage);
    }
    int getMapVal(int y, int x)
    {
        return SnakeMap[y][x]; 
    }
};
