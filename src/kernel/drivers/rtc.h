#pragma once

#include "../bridge/ports.h"
#include "../graphics/display.h"
#include "../utils/util.h"

void initRTC();

int getSeconds();
int getMinutes();
int getHours();
int getDay();
int getMonth();
int getYear();