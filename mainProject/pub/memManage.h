#ifndef MEMMANAGE_H
#define MEMMANAGE_H

#include "memPool.h"




class MemManage{



public:
    MemManage();
    ~MemManage();

    void *allocate(size_t sz);
};



#endif // MEMMANAGE_H
