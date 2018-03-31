选择排序
------
#### 算法描述
 1 依旧按照我们的排序算法，从小到大排序
 2 选择排序的特点就是从第一个位置开始，从所有的数中选出一个最小的数，放在前面即可
 3 界的控制：一共要进行总人数-1次循环
 4 每次比较：总人数-i-1次比较，将最小的值的下标放在min
 5 位置互换：swap(arr[i],arr[min])
 6 优化选择排序：使用flag？
#### 图解
![](assets/selection_sort.gif)
#### 代码实现
```c
//选择排序
#include <stdio.h>
void Print_Arr(int arr[],int len)
{
    for(int i=0;i<len;i++)
    {
        printf("%4d",arr[i]);
    }
    printf("\n");
    return;
}
void Swap_Arr(int arr[],int head,int last)
{
    int temp=arr[head];
    arr[head]=arr[last];
    arr[last]=temp;
    return;
}
void Selection_Sort(int arr[],int len)
{
    int i,j,min;
    int flag;//来进行相关的优化选择
    for(i=0;i<len;i++)
    {
        min=i;
        for(j=i;j<len;j++)
        {
            if(arr[j]<arr[min])
                min=j;
        }
        Swap_Arr(arr,i,min);
    }
    return;
}
int main() {
    int arr[10]={11,51,58,15,64,95,87,88,14,2};
    int len=sizeof(arr)/ sizeof(int);
    Print_Arr(arr,len);
    Selection_Sort(arr,len);
    Print_Arr(arr,len);
    printf("Hello, World!\n");
    return 0;
}
```
