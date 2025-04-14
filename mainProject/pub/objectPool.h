#ifndef OBJECTPOOL_H
#define OBJECTPOOL_H
#include "pub.h"


uintptr_t getNotPageMask();


typedef struct Slot
{
    Slot *_next;
} T_SLOT;

class ObjectPool;

typedef struct MemPage{
    const char      *_pLog;
    ObjectPool    *_objPool;
    MemPage       *_next;
    T_SLOT          *_unusedSlotInPage;
    size_t          _objCount;

    MemPage();
    void init(ObjectPool *objPool = nullptr);
    void push(T_SLOT *const slot);
    static MemPage* toPage(const T_SLOT *slot);
    bool isFreePage() const;
    bool isFullPage() const;
    void unusedSlot2singleList(T_SLOT* &head, T_SLOT* &tail);
    void popUnusedSlots(T_SLOT* &unusedSlots, size_t &unusedSlotCount);
} T_PAGE;

inline void T_PAGE::init(ObjectPool *objPool){
    _pLog = "MEM_PAGE_LOG";
    _objPool = objPool;
    _next = nullptr;
    _unusedSlotInPage = nullptr;
    _objCount = 0;
}

inline void T_PAGE::push(T_SLOT * const slot){
    if(nullptr == _unusedSlotInPage){
        _unusedSlotInPage = slot;
        _unusedSlotInPage->_next = _unusedSlotInPage;
    } else {
        slot->_next = _unusedSlotInPage->_next;
        _unusedSlotInPage->_next = slot;
    }
    ++_objCount;
}

inline MemPage* T_PAGE::toPage(const T_SLOT *slot){
    return reinterpret_cast<MemPage*>((uintptr_t)slot & getNotPageMask());
}

inline bool T_PAGE::isFullPage() const {
    return (0 == _objCount);
}

inline void T_PAGE::unusedSlot2singleList(T_SLOT *&head, T_SLOT *&tail){
    if(nullptr == _unusedSlotInPage){
        head = nullptr;
        tail = nullptr;
    } else if (_unusedSlotInPage->_next == _unusedSlotInPage){
        _unusedSlotInPage->_next = nullptr;
        head = _unusedSlotInPage;
        tail = _unusedSlotInPage;
    } else {
        head = _unusedSlotInPage->_next;
        _unusedSlotInPage->_next = nullptr;
        tail = _unusedSlotInPage;
    }
}
inline void T_PAGE::popUnusedSlots(T_SLOT *&unusedSlots, size_t &unusedSlotCount){
    T_SLOT* head(nullptr),*tail(nullptr);
    unusedSlot2singleList(head, tail);
    tail->_next = unusedSlots;
    unusedSlots = head;
    head = nullptr;
    tail = nullptr;
    unusedSlotCount += _objCount;
    _unusedSlotInPage = nullptr;
    _objCount = 0;
}
#define PAGE_ALIGN 17   // Page align define, page size = 2^PAGE_ALIGN
#define SLOT_ALIGN 3U   // 2U (4 Byte); 3U(8 Byte); 4U(16 Byte)

class ObjectPool{
private:
    void        *_masterPool;
    T_SLOT      *_unusedSlots;
    T_PAGE      *_usedPages;
    size_t      _oneSlotSize;
    size_t      _maxSlotsPerPage;
    size_t      _pageCount;    // the number of usedPages
    size_t      _peakPageCount;
    size_t      _liveObjCount;  // the number of usedSlot
    size_t      _totalAllocCount;
    size_t      _unusedSlotsCount;  // optimize for free unused page function
    pthread_mutex_t _memObjPoolMutex;
    bool        _beenFreeUnused;

    ObjectPool(const ObjectPool& o);
public:
    ObjectPool(size_t sz, void *master);
    ~ObjectPool();

    void    *   allocate();
    void        deallocate(void *ptr, bool bCheckValid = true);
    size_t      freeUnusedPage();
    T_PAGE *    usedPages() const;
    void    *   masterPool() const;
    size_t      liveObjCount() const;
    size_t      totalAllocCount() const;
    size_t      oneSlotSize() const;
    size_t      peakMemSize() const;
    size_t      peakPageCount() const;
    size_t      useMemSize() const;
    size_t      liveObjUseMemSize() const;
    size_t      pageCount() const;
    size_t      maxSlotsPerPage() const;

    bool        empty() { return _usedPages == nullptr; }
    bool        noFreePage() const;
    void        resetPageStatus();
    void        checkMemoryLeak(const bool isDebugMode);
    void        freeAllPages();
private:
    void        allocNewPage();
};




#endif // OBJECTPOOL_H
