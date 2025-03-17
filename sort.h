#ifndef SORT_H
#define SORT_H

#include "main.h"

class Solution4 {
public:
    /*********************快速排序***********************/
    int partition(std::vector<int>& arr, int low, int high){
        int val = arr[high];
        int i = low -1;
        for(int j = low; j < high ; ++j){
            if(arr[j] < val){
                ++i;
                swap(arr[i],arr[j]);
            }
        }
        swap(arr[i+1],arr[high]);
        return i+1;
    }
    // ascending
    void quickSort(std::vector<int>& arr, int low, int high){
        if(low < high){
            int mid = partition(arr, low, high);
            quickSort(arr, low, mid-1);
            quickSort(arr, mid+1,high);
        }
    }

    /*******************冒泡排序*************************/
    // descending
    void bubbleSort(std::vector<int>& arr){
        int len = arr.size();
        for(int i=0;i<len;++i){
            for(int j=i;j<len;++j){
                if(arr[i] < arr[j]) {
                    swap(arr[i],arr[j]);
                }
            }
        }
    }
    /*********************堆排序***********************/
    void heapify(std::vector<int>& arr, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest])
            largest = left;

        if (right < n && arr[right] > arr[largest])
            largest = right;

        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }

    void heapSort(std::vector<int>& arr, int n) {
        for (int i = n / 2 - 1; i >= 0; --i)
            heapify(arr, n, i);

        for (int i = n - 1; i > 0; --i) {
            std::swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
    }
    /********************插入排序************************/
    void insertionSort(std::vector<int>& arr) {
        int n = arr.size();
        for(int i = 1; i < n; ++i){
            int key = arr[i];
            int j = i - 1;
            while(j >= 0 && arr[j] > key){
                arr[j + 1] = arr[j];
                --j;
            }
            arr[j+1] = key;
        }
    }

};
// 1
void quickSortTest(){
    Solution4 so;
    std::vector<int> arr = {10, 7, 8, 9, 1, 5};
    int n = arr.size();
    so.quickSort(arr, 0, n - 1);
    pVector(arr,"quickSort");
}
// 2
void bubbleSortTest(){
    Solution4 so;
    std::vector<int> arr = {10, 7, 8, 9, 1, 5};
    so.bubbleSort(arr);
    pVector(arr,"bubbleSort");
}
// 3
void heapSortTest(){
    Solution4 so;
    std::vector<int> arr = {10, 7, 8, 9, 1, 5};
    int n = arr.size();
    so.heapSort(arr, n);
    pVector(arr,"heapSort");
}
// 4
void insertionSortTest(){
    Solution4 so;
    std::vector<int> arr = {10, 7, 8, 9, 1, 5};
    so.insertionSort(arr);
    pVector(arr,"insertionSort");
}

void sortTest(){
//    quickSortTest();
//    bubbleSortTest();
//    heapSortTest();
    insertionSortTest();
}



#endif // SORT_H
