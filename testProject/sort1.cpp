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
/* test 6 *******************希尔排序************************/
void insert(vector<int>& arr, int h, int i){
    int temp = arr[i];
    int k;
    for(k = i - h; k >= 0 && temp < arr[k]; k-=h){//
        arr[k+h] = arr[k];
    }
    arr[k+h] = temp;
}

void shellSort(std::vector<int>& arr){
    int n = arr.size();
    for(int h = n/2; h >0; h/=2){
        for(int i = h; i < n; ++i){
            insert(arr,h,i);
        }
    }
}
/* test 7 *******************归并排序************************/
// 递归版
//void merge(std::vector<int>& arr, int left, int mid, int right){

//}

// 非递归版
void mergeSort(std::vector<int>& arr){
    int n = arr.size();
    for(int curr_size = 1; curr_size < n; curr_size += curr_size){
        for(int left_start = 0; left_start < n - 1; left_start += 2*curr_size){
            int mid = std::min(left_start + curr_size - 1, n-1);
            int right_end = std::min(left_start + 2*curr_size - 1, n-1);

            int n1 = mid - left_start + 1;
            int n2 = right_end - mid;

            std::vector<int> L(n1), R(n2);
            for(int i = 0; i < n1; ++i)
                L[i] = arr[left_start+i];
            for(int j = 0; j < n2; ++j)
                R[j] = arr[mid+1+j];

            int i = 0, j = 0, k = left_start;
            while(i < n1 && j < n2){
                if(L[i] <= R[j]){
                    arr[k] = L[i];
                    i++;
                } else {
                    arr[k] = R[j];
                    j++;
                }
                k++;
            }

            while(i < n1){
                arr[k] = L[i];
                i++;
                k++;
            }
            while(j < n2){
                arr[k] = R[j];
                j++;
                k++;
            }
        }
    }
}
/* test 8 *******************计数排序************************/
void countingSort(std::vector<int>& arr){
    if(arr.size() < 2) return;
    int n = arr.size();
    int max = arr[0];
    int min = arr[0];
    for(int i=1; i<n; ++i){
        if(arr[i]>max)
            max = arr[i];
        if(arr[i]<min)
            min = arr[i];
    }
    int d = max-min+1;
    vector<int> temp(d,0);
    for(int i=0; i<n; ++i){
        temp[arr[i]-min]++;
    }

    int k=0;
    for(int i=0; i< d; ++i){
        for(int j = temp[i]; j > 0; j--){
            arr[k++] = i+min;
        }
    }
    return;
}

/* test 9 *******************桶排序************************/
void bucketSort(std::vector<int>& arr){
    if(arr.size() < 2) return;
    int n = arr.size();
    int max = arr[0];
    int min = arr[0];
    for(int i=1; i<n; ++i){
        if(arr[i]>max)
            max = arr[i];
        if(arr[i]<min)
            min = arr[i];
    }
    int d = max-min;
    int bucketNum = 2;
    vector<vector<int>> buckets(bucketNum);

    int bucketWidth = d / bucketNum;
    for(int i=0; i<n; ++i){
        int index = (arr[i] - min) / bucketWidth;
        if(index == bucketNum)
            index--;
        buckets[index].push_back(arr[i]);
    }
    int i=0;
    for (auto& bucket: buckets) {
        sort(bucket.begin(),bucket.end());
        for (auto& val: bucket) {
            arr[i] = val;
            ++i;
        }
    }
    return;
}
/* test 10 *******************基数排序************************/


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

TEST(sort_test, test6_shellSort){
    std::vector<int> arr = {10, 7, 8, 9, 1, 5};
    pVector(arr,"shellSort input");
    shellSort(arr);
    pVector(arr,"shellSort output");

    vector<int> rightResult = {1,5,7,8,9,10};
    EXPECT_EQ(arr, rightResult);
}

TEST(sort_test, test7_mergeSort){
    std::vector<int> arr = {10, 7, 8, 9, 1, 5};
    pVector(arr,"mergeSort input");
    mergeSort(arr);
    pVector(arr,"mergeSort output");

    vector<int> rightResult = {1,5,7,8,9,10};
    EXPECT_EQ(arr, rightResult);
}
TEST(sort_test, test8_countingSort){
    std::vector<int> arr = {10, 7, 8, 9, 1, 5};
    pVector(arr,"countingSort input");
    countingSort(arr);
    pVector(arr,"countingSort output");

    vector<int> rightResult = {1,5,7,8,9,10};
    EXPECT_EQ(arr, rightResult);
}
TEST(sort_test, test9_bucketSort){
    std::vector<int> arr = {10, 7, 8, 9, 1, 5};
    pVector(arr,"bucketSort input");
    bucketSort(arr);
    pVector(arr,"bucketSort output");

    vector<int> rightResult = {1,5,7,8,9,10};
    EXPECT_EQ(arr, rightResult);
}
