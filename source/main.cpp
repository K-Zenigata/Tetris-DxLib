#include <iostream>

#include "../include/Game.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    auto game = Game();

    // DxLib ‚ğ‰Šú‰»
    if (DxLib_Init() == -1) return -1;
    game.init();

    game.run();

    return 0;
}