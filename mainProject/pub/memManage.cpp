
#include "memManage.h"

static bool OPEN_MEMPOOL = false;
static __thread MemPool *g_memPool = nullptr;
static MemManage g_memManage;
static size_t g_maxObjSize = (1 << SLOT_ALIGN) * OBJPOOL_COUNT;



void createMemPool(){

}


void *allocate(size_t sz){
    if(sz == 0)
        return NULL;
    if(!OPEN_MEMPOOL)
        return reinterpret_cast<void*>(new char[sz]);
    if(sz > g_maxObjSize)
        return g_memManage.allocate(sz);
    if(g_memPool == nullptr)
        createMemPool();
    void *ptr = g_memPool->allocate(sz);
#ifdef DEBUG_MEM
    dbgMemPool.usedSlot(ptr);
#endif
    return ptr;
}


