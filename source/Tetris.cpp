#include "../include/Tetris.hpp"

#include <iostream>

void Tetris::Init() {
    // �R���X�g���N�^���g���ƁADxLib_Init ���܂�����Ă��Ȃ��̂ŁAInit�֐�������āA���̒��ŉ摜����荞�ށB

    // 8�����ŉ摜���i�[
    LoadDivGraph("../assets/block.png", 8, 8, 1, BLOCK_SIZE, BLOCK_SIZE, blocks);

    startPos.x = 4;
    startPos.y = -1;
}

// �����z�u
void Tetris::InitialPlacement() {
    // 1 ~ 7
    colorNum = 1 + GetRand(6);

    for (int i = 0; i < 4; i++) {
        minoPos[i].x = BLOCK_CAST[colorNum][i] % 2 + startPos.x;
        minoPos[i].y = BLOCK_CAST[colorNum][i] / 2 + startPos.y;
    }

    // �u���b�N���ςݏグ��ꂽ��AGame Over
    if (field[0][4] || field[0][5]) {
        gameOver = true;
    }
}

bool Tetris::Check() {
    for (int i = 0; i < 4; i++) {
        // ��O�Ȃ��
        if (minoPos[i].x < 0 || minoPos[i].x >= COLS || minoPos[i].y >= ROWS) {
            return 0;

        } else if (field[minoPos[i].y][minoPos[i].x])
            // field �ɉ�������̃u���b�N������Ȃ�� //

            return 0;
    }

    return true;
}

// �L�[����
void Tetris::ProcessInput() {

    // �S�ẴL�[�̉�����Ԃ��擾
    GetHitKeyStateAll(Keys);

    static int count = 0;
    if (count % INPUT_DELAY == 0) {
        // �L�[�������ꂽ��
        if (Keys[KEY_INPUT_LEFT]) {
            dx = -1;
        } else if (Keys[KEY_INPUT_RIGHT]) {
            dx = 1;
            // Square block �͉�]���Ȃ� //
        } else if (colorNum != 7 && !rotate && Keys[KEY_INPUT_UP]) {
            RotateBlock();
            rotate = true;
        } else if (Keys[KEY_INPUT_DOWN]) {
            DropBlock(DOWN_KEY_DELAY);
        }
    }
    count++;

    // �L�[�������ꂽ��
    if (!Keys[KEY_INPUT_UP]) {
        rotate = false;
    }
}

// �ړ�
void Tetris::MoveBlock() {
    for (int i = 0; i < 4; i++) {
        // ���݂�position��ޔ�
        tempPos[i] = minoPos[i];
        // �L�[���͒l�����Z
        minoPos[i].x += dx;
    }

    dx = 0;

    // ��O�A���邢�̓u���b�N�����݂���Ȃ��
    if (!Check()) {
        for (int i = 0; i < 4; i++) {
            // �ޔ�����position��Ԃ��āA���Ƃɖ߂��B
            minoPos[i] = tempPos[i];
        }
    }
}

// ��]
void Tetris::RotateBlock() {
    // [1]�̍��W�����ɉ�]����
    Vector2 p = minoPos[1];

    // rotate.png�����Ă��傤����
    for (int i = 0; i < 4; i++) {
        int x = minoPos[i].y - p.y;
        int y = minoPos[i].x - p.x;
        minoPos[i].x = p.x - x;
        minoPos[i].y = p.y + y;
    }

    if (!Check()) {
        for (int i = 0; i < 4; i++) {
            // ��L�Ɠ����ŁAcheck �� false �Ȃ�΁A�ޔ�����position��Ԃ�
            minoPos[i] = tempPos[i];
        }
    }
}

// ����
void Tetris::DeleteLine() {
    int len = ROWS - 1;
    
    // �����猩��
    for (int y = ROWS - 1; y > 0; y--) {
        int count = 0;
        
        // ��������
        for (int x = 0; x < COLS; x++) {

            // �u���b�N�������
            if (field[y][x]) count++;

            field[len][x] = field[y][x];
        }

        // ���������Ă��Ȃ����
        if (count < COLS) len--;
    }
}

// ������
void Tetris::DropBlock(int delay) {
    static int count = 0;

    if (count % delay == 0) {
        for (int i = 0; i < 4; i++) {
            tempPos[i] = minoPos[i];
            minoPos[i].y += 1;
        }

        if (!Check()) {
            for (int i = 0; i < 4; i++) {
                // �u���b�N���l�܂��Ă����ԂȂ̂ŁA���݂̃u���b�N���ł߂�
                field[tempPos[i].y][tempPos[i].x] = colorNum;
            }

            InitialPlacement();
        }
        count = 0;
    }
    count++;
}

// field�̕`��
void Tetris::DrawBoard() {
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            DrawGraph(x * BLOCK_SIZE, y * BLOCK_SIZE, blocks[field[y][x]], FALSE);
        }
    }
}

// ���ݑ��쒆�̃u���b�N��`��
void Tetris::DrawBlock() {
    for (int i = 0; i < 4; i++) {
        // colorNum �ɑI�΂ꂽ���l�ŐF������
        DrawGraph(minoPos[i].x * BLOCK_SIZE, minoPos[i].y * BLOCK_SIZE, blocks[colorNum], FALSE);
    }
}

// ���������̉摜������
void Tetris::DeleteImageGraph() {
    for (int i = 0; i < 8; i++) {
        DeleteGraph(blocks[i]);
    }
}

// Game Over �̕���
void Tetris::DrawTextString(int size, int x, int y, const char* text, int clr) {
    // �����̑傫��
    SetFontSize(size);

    // ��������ʂɏo��
    DrawString(x, y, text, clr);
}