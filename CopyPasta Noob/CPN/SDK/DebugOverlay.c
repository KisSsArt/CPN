#include "DebugOverlay.h"
#include "../Base/Interfaces/Interfaces.h"
#include "Utils.h"

BOOL DebugOverlay_screenPosition(CONST struct Vector* point, struct Vector* screen)
{
    return CALL_VIRTUAL_METHOD(BOOL(__fastcall*)(PVOID, PVOID, CONST struct Vector*, struct Vector*), interfaces.debugOverlay, 13, point, screen);
}
