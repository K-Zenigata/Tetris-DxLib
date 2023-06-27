#include "../include/Tetris.hpp"

#include <iostream>

void Tetris::Init() {
    // コンストラクタを使うと、DxLib_Init がまだされていないので、Init関数を作って、その中で画像を取り込む。

    // 8分割で画像を格納
    LoadDivGraph("../assets/block.png", 8, 8, 1, BLOCK_SIZE, BLOCK_SIZE, blocks);

    startPos.x = 4;
    startPos.y = -1;
}

// 初期配置
void Tetris::InitialPlacement() {
    // 1 ~ 7
    colorNum = 1 + GetRand(6);

    for (int i = 0; i < 4; i++) {
        minoPos[i].x = BLOCK_CAST[colorNum][i] % 2 + startPos.x;
        minoPos[i].y = BLOCK_CAST[colorNum][i] / 2 + startPos.y;
    }

    // ブロックが積み上げられたら、Game Over
    if (field[0][4] || field[0][5]) {
        gameOver = true;
    }
}

bool Tetris::Check() {
    for (int i = 0; i < 4; i++) {
        // 場外ならば
        if (minoPos[i].x < 0 || minoPos[i].x >= COLS || minoPos[i].y >= ROWS) {
            return 0;

        } else if (field[minoPos[i].y][minoPos[i].x])
            // field に何かしらのブロックがあるならば //

            return 0;
    }

    return true;
}

// キー入力
void Tetris::ProcessInput() {

    // 全てのキーの押下状態を取得
    GetHitKeyStateAll(Keys);

    static int count = 0;
    if (count % INPUT_DELAY == 0) {
        // キーが押されたら
        if (Keys[KEY_INPUT_LEFT]) {
            dx = -1;
        } else if (Keys[KEY_INPUT_RIGHT]) {
            dx = 1;
            // Square block は回転しない //
        } else if (colorNum != 7 && !rotate && Keys[KEY_INPUT_UP]) {
            RotateBlock();
            rotate = true;
        } else if (Keys[KEY_INPUT_DOWN]) {
            DropBlock(DOWN_KEY_DELAY);
        }
    }
    count++;

    // キーが離されたら
    if (!Keys[KEY_INPUT_UP]) {
        rotate = false;
    }
}

// 移動
void Tetris::MoveBlock() {
    for (int i = 0; i < 4; i++) {
        // 現在のpositionを退避
        tempPos[i] = minoPos[i];
        // キー入力値を加算
        minoPos[i].x += dx;
    }

    dx = 0;

    // 場外、あるいはブロックが存在するならば
    if (!Check()) {
        for (int i = 0; i < 4; i++) {
            // 退避したpositionを返して、もとに戻す。
            minoPos[i] = tempPos[i];
        }
    }
}

// 回転
void Tetris::RotateBlock() {
    // [1]の座標を軸に回転する
    Vector2 p = minoPos[1];

    // rotate.pngを見てちょうだい
    for (int i = 0; i < 4; i++) {
        int x = minoPos[i].y - p.y;
        int y = minoPos[i].x - p.x;
        minoPos[i].x = p.x - x;
        minoPos[i].y = p.y + y;
    }

    if (!Check()) {
        for (int i = 0; i < 4; i++) {
            // 上記と同じで、check が false ならば、退避したpositionを返す
            minoPos[i] = tempPos[i];
        }
    }
}

// 消去
void Tetris::DeleteLine() {
    int len = ROWS - 1;
    
    // 下から見る
    for (int y = ROWS - 1; y > 0; y--) {
        int count = 0;
        
        // 横を見る
        for (int x = 0; x < COLS; x++) {

            // ブロックがあれば
            if (field[y][x]) count++;

            field[len][x] = field[y][x];
        }

        // 横が揃っていなければ
        if (count < COLS) len--;
    }
}

// 落ちる
void Tetris::DropBlock(int delay) {
    static int count = 0;

    if (count % delay == 0) {
        for (int i = 0; i < 4; i++) {
            tempPos[i] = minoPos[i];
            minoPos[i].y += 1;
        }

        if (!Check()) {
            for (int i = 0; i < 4; i++) {
                // ブロックが詰まっている状態なので、現在のブロックを固める
                field[tempPos[i].y][tempPos[i].x] = colorNum;
            }

            InitialPlacement();
        }
        count = 0;
    }
    count++;
}

// fieldの描画
void Tetris::DrawBoard() {
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            DrawGraph(x * BLOCK_SIZE, y * BLOCK_SIZE, blocks[field[y][x]], FALSE);
        }
    }
}

// 現在操作中のブロックを描画
void Tetris::DrawBlock() {
    for (int i = 0; i < 4; i++) {
        // colorNum に選ばれた数値で色をつける
        DrawGraph(minoPos[i].x * BLOCK_SIZE, minoPos[i].y * BLOCK_SIZE, blocks[colorNum], FALSE);
    }
}

// メモリ内の画像を消去
void Tetris::DeleteImageGraph() {
    for (int i = 0; i < 8; i++) {
        DeleteGraph(blocks[i]);
    }
}

// Game Over の文字
void Tetris::DrawTextString(int size, int x, int y, const char* text, int clr) {
    // 文字の大きさ
    SetFontSize(size);

    // 文字を画面に出力
    DrawString(x, y, text, clr);
}