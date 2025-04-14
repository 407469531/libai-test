#include "objectPool.h"


static uintptr_t g_notPageMask = ~(uintptr_t)0 >> PAGE_ALIGN << PAGE_ALIGN;

uintptr_t getNotPageMask(){
    return g_notPageMask;
}
