#pragma once

#include "Tetris.hpp"

class Game {
   public:
    Tetris tetris;

    const int WINDOW_WIDTH = tetris.BLOCK_SIZE * tetris.COLS;
    const int WINDOW_HEIGHT = tetris.BLOCK_SIZE * tetris.ROWS;
    const int BIT_COLOR = 32;

    Game();

    void init();
    void input();
    void update();
    void draw();
    bool run();
};