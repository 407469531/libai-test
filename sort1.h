#ifndef SORT1_H
#define SORT1_H

#include "pub.h"

class Solution4 {
public:
    /*********************快速排序***********************/
    int partition(std::vector<int>& arr, int low, int high);
    // ascending
    void quickSort(std::vector<int>& arr, int low, int high);

    /*******************冒泡排序*************************/
    // descending
    void bubbleSort(std::vector<int>& arr);
    /*********************堆排序***********************/
    void heapify(std::vector<int>& arr, int n, int i);

    void heapSort(std::vector<int>& arr, int n);
    /********************插入排序************************/
    void insertionSort(std::vector<int>& arr);


};
// 1
void quickSortTest();
// 2
void bubbleSortTest();
// 3
void heapSortTest();
// 4
void insertionSortTest();

void sortTest();


#endif // SORT_H
