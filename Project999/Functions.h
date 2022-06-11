#pragma once
#ifndef FunctionsH
#define FunctionsH
//Оголошення функцій
const int maxBoardSize = 34;
void addWord(const char*, char[][maxBoardSize], int, int, int, int);
void checkBestWord(const char* [], const char[][maxBoardSize], int, int[],
    int[], int[], int, int, int, int&, int&, int&, int&, int&);
void printBoard(const char* [], const char[][maxBoardSize], int);
void printAnswer(const char* [], const char[][maxBoardSize], int);
#endif