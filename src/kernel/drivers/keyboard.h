#pragma once
#include "../bridge/ports.h"

unsigned char qwertylow[128];
unsigned char qwertyup[128];

unsigned char getLowerChar(unsigned char scancode);
unsigned char getUpperChar(unsigned char scancode);
void callKeyboard();

unsigned int uppercase;