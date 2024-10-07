#pragma once

struct workspacePos_t{
    int col;
    int row;
};

int handleInput(const int keyPress, struct workspacePos_t *workspacePos);