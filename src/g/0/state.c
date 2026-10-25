/* g/0/state.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: g/0/state.c:59  [size]
void __cdecl State_Close()
{
  QTask_DeleteQTaskEvent(State_eGetStateQTaskEvent);
}

// source: g/0/state.c:75  [size]
__int16 __cdecl State_GetGetStateQTaskEvent()
{
  return State_eGetStateQTaskEvent;
}

// source: g/0/state.c:97  [anchor-mhash]
void __cdecl State_Init(
        struct State_s *ptState,
        void (__cdecl *pfSignalHandler)(struct State_s *, struct QTask_s *),
        void (__cdecl **apfState)(struct State_s *, struct QTask_s *),
        void (__cdecl **apfExitState)(struct State_s *, struct QTask_s *),
        int nState,
        int nSequence,
        struct Sequence_t *ptSequence)
{
  struct State_s *v7; // eax
  struct State_s **v8; // edx
  struct State_s *v9; // ecx

  *v8 = ptState;
  v8[2] = (struct State_s *)pfSignalHandler;
  v8[1] = v9;
  v8[5] = v7;
  v8[4] = (struct State_s *)-1;
  v8[3] = nullptr;
  v8[6] = *((struct State_s **)&v9->pfSignalHandler + (_DWORD)v7);
  v8[7] = (struct State_s *)apfState;
  v8[9] = (struct State_s *)apfExitState;
  v8[8] = (struct State_s *)-1;
  memset(v8 + 10, 0, 0x28u);
}

// source: g/0/state.c:137  [anchor-mhash]
void __cdecl State_Run(struct State_s *ptState, struct QTask_s *ptQTask)
{
  int v2; // ebx
  int v3; // edi
  struct SequenceWork_t *atSequenceWork; // eax
  unsigned __int8 nSequenceItem; // bl
  struct Sequence_t *ptSequence; // edx
  struct SequenceItem_t *ptSequenceItem; // ebp
  struct Sequence_t *v8; // edx
  struct SequenceItem_t *v9; // ecx
  bool v10; // zf
  unsigned int bSignal; // [esp+8h] [ebp-Ch]
  int nSequence; // [esp+10h] [ebp-4h]

  v2 = ptState->nSequence;
  bSignal = ptState->bSignal;
  nSequence = v2;
  ptState->pfSignalHandler(ptState, ptQTask);
  v3 = 0;
  ptState->nCompletedSequence = -1;
  if ( v2 > 0 )
  {
    atSequenceWork = ptState->atSequenceWork;
    while ( 1 )
    {
      nSequenceItem = atSequenceWork->nSequenceItem;
      ptSequence = ptState->ptSequence;
      ptSequenceItem = ptSequence[v3].ptSequenceItem;
      v8 = &ptSequence[v3];
      v9 = &ptSequenceItem[atSequenceWork->nSequenceItem];
      v10 = v9->isSignalState ? (bSignal & v9->bSignal) == v9->bSignal : (bSignal & v9->bSignal) == 0;
      if ( !v10 )
        break;
      atSequenceWork->nSequenceItem = nSequenceItem + 1;
      if ( nSequenceItem + 1 == v8->nSequenceItem )
      {
        ptState->nCompletedSequence = v3;
LABEL_12:
        atSequenceWork->nSequenceItem = 0;
        atSequenceWork->nSignalTimer = 0;
        goto LABEL_13;
      }
      atSequenceWork->nSignalTimer = v8->ptSequenceItem[(unsigned __int8)(nSequenceItem + 1)].nSignalTime;
LABEL_13:
      ++v3;
      ++atSequenceWork;
      if ( v3 >= nSequence )
        goto LABEL_14;
    }
    if ( !nSequenceItem )
      goto LABEL_13;
    v10 = atSequenceWork->nSignalTimer-- == 1;
    if ( !v10 )
      goto LABEL_13;
    goto LABEL_12;
  }
LABEL_14:
  ptState->pfState(ptState, ptQTask);
}
