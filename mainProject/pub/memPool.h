#ifndef MEMPOOL_H
#define MEMPOOL_H

#include "objectPool.h"


#define OBJPOOL_COUNT 16

class MemPool {
    typedef ObjectPool  T_OBJPOOL;
    typedef MemPage     T_PAGE;

private:

    T_OBJPOOL **    _objPools;
    size_t          _liveObjCount;

public:

    void * allocate(size_t sz);


};

#endif // MEMPOOL_H
