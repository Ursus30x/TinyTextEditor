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

#define LEFT    0
#define RIGHT   1

void moveTextBuffer(const int startRow,const int startCol,const int endRow,const int endCol,const int side){
    char bufferCpy[1024];
    int amountCol = abs(startCol - endCol),
        amountRow = abs(startRow - endRow);

    if(side == LEFT){
        strcpy(bufferCpy,&textBuffer.buffer[startRow][startCol]);
        strcpy(&textBuffer.buffer[endRow][endCol],bufferCpy);
        textBuffer.lastCharPos[startRow] -= amountCol;
    }
    else if(side == RIGHT){
        strcpy(bufferCpy,&textBuffer.buffer[startRow][startCol]);
        strcpy(&textBuffer.buffer[endRow][endCol],bufferCpy);
        textBuffer.lastCharPos[startRow] += amountCol;
    }
}

void insertNewLineTextBuffer(const int row,const int col){
    char lineTransfer[1024];

    strcpy(lineTransfer,&textBuffer.buffer[row][col]);


    free(textBuffer.buffer[BUFFER_LINE_AMOUNT-1]);
 
    for(int i = BUFFER_LINE_AMOUNT-2;i>=row;i--){
        textBuffer.buffer[i+1] = textBuffer.buffer[i];
    }

    

    textBuffer.buffer[row+1] = (char*)malloc(BUFFER_LINE_LENGTH*sizeof(char));
    memset(textBuffer.buffer[row+1],'\0',BUFFER_LINE_LENGTH);
    strcpy(textBuffer.buffer[row+1],&textBuffer.buffer[row][col]);

    textBuffer.buffer[row][col] = '\n';
    textBuffer.buffer[row][col+1] = '\0';
    textBuffer.lastCharPos[row] = col;

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

