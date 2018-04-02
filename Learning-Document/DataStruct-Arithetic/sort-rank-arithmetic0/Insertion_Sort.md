插入排序
------
####  算法
  一般来说，插入排序都采用in-place在数组上排序
  具体算法如下所示：
   1 从第一个元素开始，该元素可以认为已经被排序
   2 取出下一个元素，在已排序的序列里从后往前扫描
   3 如果该元素大于新元素，那么就把该元素移到下一个位置
   4 重复3，直到该元素小于等于新元素
   5 将新元素插到该元素位置后面
   6 重复步骤2-6

####  动态演示
![inserion_sort](assets/insertion_sort.gif)
![insertion_sort](assets/inserion_sort1.gif)
####  实现代码

```c
//插入排序
//插入排序
#include <stdio.h>

void print_arr(int arr[], int len) {
    for (int i = 0; i < len; i++) {
        printf("%4d", arr[i]);
    }
    printf("\n");
}

void insertion_sort(int arr[], int len) {
    int i, j, temp;
    for (i = 1; i < len; i++) {
        temp = arr[i];
        for (j = i - 1; j >= 0; j--) {
            if (arr[j] > temp) {
                arr[j + 1] = arr[j];
                arr[j] = temp;//以防止这是最小的数字，最后没有插入到头结点
                print_arr(arr, len);
            }
            else if (arr[j] < temp) {
                //arr[j + 1] = temp;
                //printf(arr, len);
                break;
            }
        }
    }
    return;
}

int main() {
    int arr[10] = {11, 51, 58, 15, 64, 95, 87, 88, 14, 2};
    int len = sizeof(arr) / sizeof(int);
    print_arr(arr, len);
    insertion_sort(arr, len);
    print_arr(arr, len);
    printf("Hello, World!\n");
    return 0;
}
```
#### 特点：
  + 插入排序平均需要```N^2/4```次比较和```N^2/4```次交换。</br>
    最坏的情况需要```N^2/2```次比较和交换。
    最好的情况，所有序列都排好顺序，插入排序只需要```N-1```次比较，并没有有交换
  + 插入排序中，元素交换的次数等于序列中逆序元素的对数。
  + 总体来说，插入排序对于部分有序序列以及元素个数比较小的序列是一种比较有效的方式。
