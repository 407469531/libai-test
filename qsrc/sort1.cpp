#include "pub.h"

/* test 1 ********************快速排序***********************/
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
void quickSort(std::vector<int>& arr, int low, int high){
    if(low < high){
        int mid = partition(arr, low, high);
        quickSort(arr, low, mid-1);
        quickSort(arr, mid+1,high);
    }
}
/* test 2 ******************冒泡排序*************************/
void bubbleSort(std::vector<int>& arr){
    if(arr.size() < 2)
        return;
    int len = arr.size();
    for(int i=0;i<len;++i){
        bool isNoSwap = true;
        for(int j=0; j<len-i-1; ++j){
            if(arr[j+1] < arr[j]){
                isNoSwap = false;
                swap(arr[j], arr[j+1]);
            }
        }
        if(isNoSwap)
            break;
    }
}

/* test 3 ********************堆排序***********************/
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
/* test 4 *******************插入排序************************/
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
/* test 5 *******************选择排序************************/
void selectSort(std::vector<int>& arr) {
    int n = arr.size();
    for(int i = 0; i < n; ++i){
        int min = i;
        for(int j = i+1; j < n; ++j){
            if(arr[j] < arr[min])
                min = j;
        }
        swap(arr[min],arr[i]);
    }
}

/*********************测试例子构造***********************/
TEST(sort_test, test1_quickSort){
    std::vector<int> arr = {10, 7, 8, 9, 1, 5};
    int n = arr.size();
    pVector(arr,"quickSort input");
    quickSort(arr, 0, n - 1);
    pVector(arr,"quickSort output");

    vector<int> rightResult = {1,5,7,8,9,10};
    EXPECT_EQ(arr, rightResult);
}

TEST(sort_test, test2_bubbleSort){
    std::vector<int> arr = {10, 7, 8, 9, 1, 5};
    pVector(arr,"bubbleSort input");
    bubbleSort(arr);
    pVector(arr,"bubbleSort output");

    vector<int> rightResult = {1,5,7,8,9,10};
    EXPECT_EQ(arr, rightResult);
}

TEST(sort_test, test3_heapSort){
    std::vector<int> arr = {10, 7, 8, 9, 1, 5};
    int n = arr.size();
    pVector(arr,"heapSort input");
    heapSort(arr, n);
    pVector(arr,"heapSort output");

    vector<int> rightResult = {1,5,7,8,9,10};
    EXPECT_EQ(arr, rightResult);
}

TEST(sort_test, test4_insertionSort){
    std::vector<int> arr = {10, 7, 8, 9, 1, 5};
    pVector(arr,"insertionSort input");
    insertionSort(arr);
    pVector(arr,"insertionSort output");

    vector<int> rightResult = {1,5,7,8,9,10};
    EXPECT_EQ(arr, rightResult);
}

TEST(sort_test, test5_selectSort){
    std::vector<int> arr = {10, 7, 8, 9, 1, 5};
    pVector(arr,"selectSort input");
    selectSort(arr);
    pVector(arr,"selectSort output");

    vector<int> rightResult = {1,5,7,8,9,10};
    EXPECT_EQ(arr, rightResult);

}
