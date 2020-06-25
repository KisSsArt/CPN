#pragma once

#include <Windows.h>

VOID Surface_setDrawColor(INT, INT, INT, INT);
VOID Surface_setDrawColor2(FLOAT[3], INT);
VOID Surface_drawOutlinedRect(FLOAT, FLOAT, FLOAT, FLOAT);
VOID Surface_drawLine(FLOAT, FLOAT, FLOAT, FLOAT);
VOID Surface_setTextFont(UINT);
VOID Surface_setTextColor(FLOAT[3], INT);
VOID Surface_setTextPosition(FLOAT, FLOAT);
VOID Surface_printText(PCWSTR);
VOID Surface_getScreenSize(INT*, INT*);
VOID Surface_unlockCursor(VOID);
VOID Surface_getTextSize(UINT, PCWSTR, INT*, INT*);
