#include "pub.h"

size_t getMemInUse(){
    size_t curMemInUse(0);
    FILE *fd(NULL);
    char fileName[64] = {0};
    snprintf(fileName, 64, "/proc/%d/status", getpid());
    if(NULL == (fd = fopen(fileName, "r"))){
        return 0;
    }
    char lineBuff[512];
    while(fgets(lineBuff, sizeof(lineBuff), fd)){
        if(1 == sscanf(lineBuff, "VmRSS:\t %zu kB\n", &curMemInUse))
            break;
    }
    fclose(fd);
    curMemInUse <<= 10;
    return curMemInUse;
}
std::string memStr(size_t bytes){
    char mem[64];
    snprintf(mem, 64, "%zu KB", bytes >> 10);
    return mem;
}

MemStamp::~MemStamp(){
    if(_startMem){
        size_t endMem = getMemInUse();
        if(endMem > _startMem)
            printf("MemStamp[%s]: incrMem:%s MemInUse:%s", _name?_name:"", memStr(endMem - _startMem).c_str(), memStr(endMem).c_str());
        else
            printf("MemStamp[%s]: incrMem:%s MemInUse:%s", _name?_name:"", memStr(_startMem - endMem).c_str(), memStr(endMem).c_str());
    }
}
