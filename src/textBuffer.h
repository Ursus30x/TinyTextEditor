#pragma once
#include <stdbool.h>


//idk thats for now, find better solution later

#define BUFFER_LINE_AMOUNT 1024
#define BUFFER_LINE_LENGTH 1024

struct textBuffer_t{
    char* buffer[BUFFER_LINE_AMOUNT];
    int lastCharPos[BUFFER_LINE_AMOUNT];
};

int initTextBuffer();

void writeCharToTextBuffer(const char c,const int row,const int col);

bool checkIfNullTextBuffer(const int row, const int col);

//LEFT = 0
//RIGHT = 1
void moveTextBuffer(const int startRow,const int startCol,const int endRow,const int endCol,const int side);

void insertNewLineTextBuffer(const int row,const int col);

int freeTextBuffer();

struct textBuffer_t* getTextBufferHandle();

