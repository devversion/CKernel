#pragma once
#include "ports.h"

void setCursorPositon(const int position);
short getCursorPosition();

void clearScreen();

void setChar(int position, unsigned char c);

void printChar(unsigned char c);
void printString(const char* _message);
void printLine(const char* _message);