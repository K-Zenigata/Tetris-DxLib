#include <iostream>
#include "../include/Game.hpp"

Game::Game() {
    // log.txt ���o�͂��Ȃ�
    SetOutApplicationLogValidFlag(false);

    // �E�B���h�E���[�h�ɐݒ�
    ChangeWindowMode(true);

    // window �̃T�C�Y
    // �𑜓x�̐ݒ� (��, ����, �F) �F�́A32�ŌŒ��OK
    SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_COLOR);

    // caption �̕�����
    SetMainWindowText("Tetris DxLib");

    // window �̔w�i�F
    SetBackgroundColor(0, 255, 0);

    // ��A�N�e�B�u��Ԃł��ғ�
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

        // ����ʂ̕`��
        ScreenFlip();
    }

    // �L�[���͂�҂�
    WaitKey();

    // �摜����������������� ���ꂽ�Ԃ񂢂�Ȃ� DxLib_End() �ɂ���ď��������Ǝv��
    tetris.DeleteImageGraph();

    // DxLib ���I��
    DxLib_End();

    return 0;
}