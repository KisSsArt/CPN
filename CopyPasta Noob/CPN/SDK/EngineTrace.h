#pragma once

#include <stdbool.h>

#include "Utils.h"
#include "Vector.h"

typedef struct Ray {
    struct Vector start;
    FLOAT pad;
    struct Vector delta;
    BYTE pad2[40];
    bool isRay;
    bool isSwept;
} Ray;

typedef struct TraceFilter {
    PVOID vmt;
    PVOID skip;
} TraceFilter;

VOID TraceFilter_init(TraceFilter*);

typedef enum HitGroup {
    HitGroup_Invalid = -1,
    HitGroup_Generic,
    HitGroup_Head,
    HitGroup_Chest,
    HitGroup_Stomach,
    HitGroup_LeftArm,
    HitGroup_RightArm,
    HitGroup_LeftLeg,
    HitGroup_RightLeg,
    HitGroup_Gear = 10
} HitGroup;

FLOAT HitGroup_getDamageMultiplier(INT);
BOOLEAN HitGroup_isArmored(INT, BOOLEAN);

typedef struct TraceSurface {
    PCSTR name;
    SHORT surfaceProps;
    USHORT flags;
} TraceSurface;

typedef struct Trace {
    struct Vector startpos;
    struct Vector endpos;
    BYTE pad[20];
    FLOAT fraction;
    INT contents;
    USHORT dispFlags;
    bool allSolid;
    bool startSolid;
    BYTE pad1[4];
    TraceSurface surface;
    HitGroup hitgroup;
    BYTE pad2[4];
    PVOID entity;
    INT hitbox;
} Trace;

VOID EngineTrace_traceRay(const Ray*, UINT, const TraceFilter*, Trace*);
