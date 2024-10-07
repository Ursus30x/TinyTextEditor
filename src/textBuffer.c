#include "textBuffer.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_LINE_AMOUNT 1024
#define BUFFER_LINE_LENGTH 1024

struct textBuffer_t textBuffer;

int initTextBuffer(){
    for(int i = 0;i<BUFFER_LINE_AMOUNT;i++){
        textBuffer.buffer[i] = (char*)malloc(BUFFER_LINE_LENGTH * sizeof(char));
        textBuffer.lastCharPos[i] = 0;
        if(textBuffer.buffer[i] == NULL)return 1;

        memset(textBuffer.buffer[i],'\0',BUFFER_LINE_LENGTH);

    }

    return 0;
}

void writeCharToTextBuffer(const char c,const int row,const int col){
    textBuffer.buffer[row][col] = c;
}

bool checkIfNullTextBuffer(const int row, const int col){
    if(textBuffer.buffer[row][col] == '\0')return true;
    else return false;
}

int freeTextBuffer(){
    for(int i = 0;i<BUFFER_LINE_AMOUNT;i++){
        free(textBuffer.buffer[i]);
    }
    return 0;
}

struct textBuffer_t* getTextBufferHandle(){
    return &textBuffer;
}

