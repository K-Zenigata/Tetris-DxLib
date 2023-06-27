#pragma once

#include "DxLib/DxLib.h"

struct Vector2 {
    int x, y;
};

class Tetris {
   public:
    static const int BLOCK_SIZE = 32;
    static const int ROWS = 20;
    static const int COLS = 10;
    const int INPUT_DELAY = 5;
    const int BLOCK_DOWN_DELAY = 30;
    const int DOWN_KEY_DELAY = 1;

    int field[ROWS][COLS] = {0};

    // image 格納
    int blocks[8];

    // 操作中のブロックの座標を格納
    Vector2 minoPos[4];

    // 退避用の座標を格納
    Vector2 tempPos[4];

    // ブロックの配置 tetris_block.pngを見てちょうだい
   const int BLOCK_CAST[8][4] = {
        0, 0, 0, 0,  // null
        1, 3, 5, 7,  // I
        2, 4, 5, 7,  // Z
        3, 5, 4, 6,  // S
        3, 5, 4, 7,  // T
        2, 3, 5, 7,  // L
        3, 5, 7, 6,  // J
        2, 3, 4, 5,  // O
    };

    Vector2 startPos;
    int colorNum;
    int dx;
    bool rotate = 0;

    bool gameOver = false;

    char Keys[256];

    void Init();
    void InitialPlacement();
    bool Check();
    void ProcessInput();
    void MoveBlock();
    void RotateBlock();
    void DeleteLine();

    // delay
    void DropBlock(int);
    
    void DrawBoard();
    void DrawBlock();
    void DeleteImageGraph();

    // fontSize, x, y, str, color
    void DrawTextString(int, int , int, const char*, int);
};