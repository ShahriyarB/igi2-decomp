/* Two functions the C cannot express, as the retail instructions (overrides/<name>.c remove the
   decompiled versions).

   The "no context" event handlers are called with the task alone ("push esi; call ecx"), yet some
   read a second argument: ModelObjParameters_DeSerializeHandler takes the deserialization context
   from it. What they find in that slot is the edi the trigger saved on entry, which
   CallQueue_CallHandlersRecursively keeps its queue in (and, one level down, the event number the
   trigger keeps in edi). A C trigger leaves something else there: the second mission restart then
   deserialized objects with a garbage context and crashed. These keep retail's stack and registers.
   Not built on igi2.h: the globals are used by their retail addresses. */

#define QTASK_STACK_OFFSET 0x849C7C0      /* QTask_nProtectedQTaskStackOffset */
#define QTASK_STACK 0x849C7E0             /* QTask_atProtectedQTaskStack[].ptQTask */
#define QTASK_STACK_PREV 0x849C7DC        /* the same array, one entry lower */
#define QTASK_FINAL_EVENT 0x8396DC0       /* QTask_aatQTaskFinalEvent[event][type].pfHandler */
#define CALLQUEUE_FREE 0x7AC0FCC          /* CallQueue_ptFirstFreeItem */

struct QTask_s;
struct CallQueue_t;
void __cdecl QTask_TriggerQTaskEventRecursively(struct QTask_s *ptQTask, unsigned short eQTaskEvent, void *pxContext);

/* retail 0x40B570 */
__declspec(naked) void __cdecl QTask_TriggerQTaskEventRecursivelyNoContext(struct QTask_s *ptQTask, int eQTaskEventNoContext)
{
    __asm {
        mov     eax, ds:[QTASK_STACK_OFFSET]
        push    esi
        mov     esi, [esp+8]                    ; ptQTask
        push    edi
        mov     edi, [esp+10h]                  ; eQTaskEventNoContext
        mov     edx, edi
        imul    edx, edx, 1FFh
        mov     ds:[QTASK_STACK + eax*4], esi
        movzx   ecx, word ptr [esi+24h]
        add     ecx, edx
        mov     ecx, ds:[QTASK_FINAL_EVENT + ecx*4]
        inc     eax
        test    ecx, ecx
        mov     ds:[QTASK_STACK_OFFSET], eax
        jz      no_handler
        push    esi                             ; the task; [esp+8] in the handler is the saved edi
        call    ecx
        mov     eax, ds:[QTASK_STACK_OFFSET]
        add     esp, 4
    no_handler:
        cmp     esi, ds:[QTASK_STACK_PREV + eax*4]
        jnz     done
        mov     ecx, [esi+8]                    ; tQTaskChildren.ptHead
        cmp     dword ptr [ecx], 0
        jz      done
        test    ecx, ecx
        jz      done
    next_child:
        mov     esi, [ecx]
        test    esi, esi
        jz      no_next
        mov     edx, [esi]
        neg     edx
        sbb     edx, edx
        and     edx, esi
        jmp     have_next
    no_next:
        xor     edx, edx
    have_next:
        mov     ds:[QTASK_STACK + eax*4], edx
        inc     eax
        push    edi
        push    ecx
        mov     ds:[QTASK_STACK_OFFSET], eax
        call    QTask_TriggerQTaskEventRecursivelyNoContext
        mov     eax, ds:[QTASK_STACK_OFFSET]
        mov     ecx, ds:[QTASK_STACK_PREV + eax*4]
        add     esp, 8
        dec     eax
        test    ecx, ecx
        jnz     next_child
    done:
        dec     eax
        pop     edi
        mov     ds:[QTASK_STACK_OFFSET], eax
        pop     esi
        ret
    }
}

/* retail 0x57A6E0, which takes ptQueue in edi: here from the stack as the C calls it, with the
   caller's edi kept */
__declspec(naked) void __cdecl CallQueue_CallHandlersRecursively(struct CallQueue_t *ptQueue)
{
    __asm {
        push    edi
        mov     edi, [esp+8]                    ; ptQueue
        push    esi
        mov     esi, [edi]
        test    esi, esi
        jz      emptied
    next_item:
        mov     eax, [esi+0Ch]
        test    eax, eax
        mov     ecx, [esi+4]
        jz      with_context
        mov     eax, [esi+8]
        push    eax                             ; eQTaskEventNoContext
        push    ecx                             ; ptQTask
        call    QTask_TriggerQTaskEventRecursivelyNoContext
        add     esp, 8
        jmp     item_done
    with_context:
        mov     edx, [esi+10h]
        xor     eax, eax
        mov     ax, [esi+8]
        push    edx                             ; pxContext
        push    eax                             ; eQTaskEvent
        push    ecx                             ; ptQTask
        call    QTask_TriggerQTaskEventRecursively
        add     esp, 0Ch
    item_done:
        mov     eax, [esi]
        test    eax, eax
        mov     edx, ds:[CALLQUEUE_FREE]
        mov     [esi], edx
        mov     ds:[CALLQUEUE_FREE], esi
        mov     esi, eax
        jnz     next_item
    emptied:
        mov     [edi+4], edi
        mov     dword ptr [edi], 0
        pop     esi
        pop     edi
        ret
    }
}
