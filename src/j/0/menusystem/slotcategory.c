/* j/0/menusystem/slotcategory.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/menusystem/slotcategory.c:41  [anchor-mhash]
void __cdecl SlotCategory_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].ptNext = *((struct QTask_s **)pxContext + 8);
  *(_DWORD *)&ptQTask[2].eQTaskType = *((_DWORD *)pxContext + 9);
  ptQTask[3].ptNext = *((struct QTask_s **)pxContext + 10);
  ptQTask[3].ptPrev = *((struct QTask_s **)pxContext + 11);
  strncpy((char *)&ptQTask[1].ptPrev, (char *)pxContext, 0x20u);
  *(_DWORD *)&ptQTask[1].eQTaskType = -1;
  ptQTask[2].ptNext = (struct QTask_s *)-1;
  ptQTask[2].ptPrev = (struct QTask_s *)-1;
  ptQTask[2].tQTaskChildren.ptHead = (struct QTask_s *)-1;
  ptQTask[2].tQTaskChildren.ptMiddle = (struct QTask_s *)-1;
  ptQTask[2].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  ptQTask[2].tQTaskRefList.ptHead = (struct QReference_s *)-1;
  ptQTask[2].tQTaskRefList.ptMiddle = (struct QReference_s *)-1;
  ptQTask[2].tQTaskRefList.ptTail = (struct QReference_s *)-1;
  ptQTask[2].ptParent = (struct QTask_s *)-1;
}

// source: j/0/menusystem/slotcategory.c:82  [size]
void __cdecl SlotCategory_RunHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/menusystem/slotcategory.c:100  [anchor-mhash]
struct SlotItem_s *__cdecl SlotCategory_GetItem(struct SlotCategory_s *ptSlotCategory, int nSlot)
{
  return ptSlotCategory->aItems[nSlot].nItemID == -1 ? nullptr : &ptSlotCategory->aItems[nSlot];
}

// source: j/0/menusystem/slotcategory.c:132  [anchor-mhash]
enum bool __cdecl SlotCategory_isSlotEnabled(struct SlotCategory_s *ptSlotCategory, int nSlot)
{
  int nItemID; // eax

  nItemID = ptSlotCategory->aItems[nSlot].nItemID;
  return nItemID != -1 && ptSlotCategory->pfItemEnabled(nItemID);
}

// source: j/0/menusystem/slotcategory.c:150  [size]
struct SlotCategory_s *__cdecl SlotCategory_GetClickedCB(
        struct SlotCategory_s *ptSlotCategory)
{
  return (struct SlotCategory_s *)ptSlotCategory->pfItemClicked;
}

// source: j/0/menusystem/slotcategory.c:169  [size]
enum bool __cdecl SlotCategory_isSlotEmpty(
        struct SlotCategory_s *ptSlotCategory,
        int nSlot)
{
  return ptSlotCategory->aItems[nSlot].nItemID == -1;
}

// source: j/0/menusystem/slotcategory.c:194  [anchor-mhash]
enum bool __cdecl SlotCategory_isEmpty(struct SlotCategory_s *ptSlotCategory)
{
  int v1; // eax
  struct SlotItem_s *i; // ecx

  v1 = 0;
  for ( i = ptSlotCategory->aItems; i->nItemID == -1; ++i )
  {
    if ( ++v1 >= 10 )
      return true;
  }
  return false;
}

// source: j/0/menusystem/slotcategory.c:223  [anchor-strings]
struct SlotCategory_s *__cdecl SlotCategory_SetSlotText(
        struct SlotCategory_s *ptSlotCategory,
        int nSlot)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zText[60]; };
    struct { char igi2_o1[60]; char zCB[60]; };
    char igi2_extent[120];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int nItemID; // esi

  if ( (unsigned int)nSlot > 9 )
  {
    _snprintf(igi2_frame.zText, 0x3Cu, "Out of range:%d", nSlot);
    return (struct SlotCategory_s *)MenuText_SetText(-1, igi2_frame.zText);
  }
  else
  {
    nItemID = ptSlotCategory->aItems[nSlot].nItemID;
    if ( nItemID == -1 )
    {
      strncpy(igi2_frame.zText, "----EMPTY----", 0x3Cu);
      return (struct SlotCategory_s *)MenuText_SetText(-1, igi2_frame.zText);
    }
    else
    {
      ptSlotCategory->pfItemText(nItemID, igi2_frame.zCB);
      _snprintf(igi2_frame.zText, 0x3Cu, "%d. %s", nSlot, igi2_frame.zCB);
      return (struct SlotCategory_s *)MenuText_SetText(nItemID, igi2_frame.zText);
    }
  }
}

// source: j/0/menusystem/slotcategory.c:266  [size]
struct QTask_s *__cdecl SlotCategory_New(
        struct QTask_s *ptParentQTask,
        struct SlotCategoryCreateContext_s *ptCreateContext)
{
  return QTask_NewFn(ptParentQTask, SlotCategory_eQTaskType, ptCreateContext);
}

// source: j/0/menusystem/slotcategory.c:280  [size]
unsigned __int16 __cdecl SlotCategory_GetQTaskType()
{
  return SlotCategory_eQTaskType;
}

// source: j/0/menusystem/slotcategory.c:296  [size]
struct SlotItem_s *__cdecl SlotCategory_Add(
        struct QTask_s *ptQTask,
        int nSlot,
        struct SlotItem_s *ptNewItem)
{
  int nItemID; // ecx

  nItemID = ptNewItem->nItemID;
  *((_DWORD *)&ptQTask[1].eQTaskType + nSlot) = nItemID;
  return (struct SlotItem_s *)ptQTask;
}

// source: j/0/menusystem/slotcategory.c:325  [size]
void __cdecl SlotCategory_Close()
{
  QTask_DeleteQTaskType(SlotCategory_eQTaskType);
}

// source: j/0/menusystem/slotcategory.c:338  [anchor-hash]
void __cdecl SlotCategory_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("SlotCategory", 128, BaseQTaskType, 0, 0);
  SlotCategory_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, SlotCategory_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, (void (__cdecl *)(struct QTask_s *))SlotCategory_RunHandler);
}
