#pragma once

#include "ports.h"
#include "display.h"
#include "util.h"

void initRTC();

int getSeconds();
int getMinutes();
int getHours();
int getDay();
int getMonth();
int getYear();