/* h/1/simbonedyncubeobj.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/1/simbonedyncubeobj.c:35  [anchor-strings]
void __cdecl SimBoneDynCubeObj_Open()
{
  SimBoneDynCubeObj_eQTaskType = QTask_NewQTaskType("SimBoneDynCubeObj", 504, BoneDynCubeObj_eQTaskType, 0, 0);
}

// source: h/1/simbonedyncubeobj.c:51  [size]
void __cdecl SimBoneDynCubeObj_Close()
{
  QTask_DeleteQTaskType(SimBoneDynCubeObj_eQTaskType);
}

// source: h/1/simbonedyncubeobj.c:73  [anchor-mhash]
void __cdecl SimBoneDynCubeObj_ApplyWings(
        struct SimBoneDynCubeObj_t *ptObject,
        struct Wing_t *ptWingList,
        int nWings,
        float vARCoeff,
        struct real32x3_t *ptWindVel)
{
  float vY; // esi
  float vZ; // edx
  struct real32x3_t tWindVel; // [esp+4h] [ebp-Ch] BYREF

  tWindVel.vX = ptObject->tSim.tPhysics.tCMVel.vX;
  vY = ptObject->tSim.tPhysics.tCMVel.vY;
  vZ = ptObject->tSim.tPhysics.tCMVel.vZ;
  tWindVel.vX = -tWindVel.vX;
  tWindVel.vY = -vY;
  tWindVel.vZ = -vZ;
  if ( ptWindVel )
  {
    tWindVel.vX = tWindVel.vX + ptWindVel->vX;
    tWindVel.vY = tWindVel.vY + ptWindVel->vY;
    tWindVel.vZ = tWindVel.vZ + ptWindVel->vZ;
  }
  Wing_ApplyAirResistance(
    ptWingList,
    nWings,
    vARCoeff,
    &ptObject->tSim.tPhysics,
    &ptObject->tBoneDynCubeObj.tModelObj.tOrientation,
    &tWindVel);
}

// source: h/1/simbonedyncubeobj.c:103  [size]
unsigned __int16 __cdecl SimBoneDynCubeObj_GetQTaskType()
{
  return SimBoneDynCubeObj_eQTaskType;
}
