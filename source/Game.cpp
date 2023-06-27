#include <iostream>
#include "../include/Game.hpp"

Game::Game() {
    // log.txt を出力しない
    SetOutApplicationLogValidFlag(false);

    // ウィンドウモードに設定
    ChangeWindowMode(true);

    // window のサイズ
    // 解像度の設定 (幅, 高さ, 色) 色は、32で固定でOK
    SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_COLOR);

    // caption の文字列
    SetMainWindowText("Tetris DxLib");

    // window の背景色
    SetBackgroundColor(0, 255, 0);

    // 非アクティブ状態でも稼動
    SetAlwaysRunFlag(true);
}

void Game::init() {
    tetris.Init();
    tetris.InitialPlacement();
}

void Game::input() { tetris.ProcessInput(); }

void Game::update() {
    tetris.DropBlock(tetris.BLOCK_DOWN_DELAY);
    tetris.MoveBlock();
    tetris.DeleteLine();
}

void Game::draw() {
    tetris.DrawBoard();
    tetris.DrawBlock();
}

bool Game::run() {

    SetDrawScreen(DX_SCREEN_BACK);

    // Game loop
    while (!ProcessMessage() && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
        input();
        update();

        ClearDrawScreen();

        draw();

        if (tetris.gameOver) {
            // fontSize, x, y, str, color
            tetris.DrawTextString(60, 28, 200, "Game Over", GetColor(255, 10, 0));

            ScreenFlip();
            break;
        }

        // 裏画面の描画
        ScreenFlip();
    }

    // キー入力を待つ
    WaitKey();

    // 画像情報をメモリから消去 これたぶんいらない DxLib_End() によって消去されると思う
    tetris.DeleteImageGraph();

    // DxLib を終了
    DxLib_End();

    return 0;
}