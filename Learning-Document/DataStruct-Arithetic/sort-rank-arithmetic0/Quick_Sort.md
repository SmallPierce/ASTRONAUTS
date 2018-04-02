快速排序
------
#### 算法原理
  核心算法：
  1 先从数列中选取一个数字作为基准数
  2 以此基准数，将数列化成两个分区，左边是比他大的数字，右边是比他要小的部分
  3 对左右分区分别继续执行1-2，直到分区为1，之后返回就好。

  >核心部分：如何将基准数字放在最后要放在的位置
  > 1 选择第一个数```a[var]```，定义``` i=0,j=last,mid=0```
  > 2 从后面开始进行比较```a[var]>arr[j]?swap(arr[var],arr[j]):j--```
  >> key是否比选量大?两个互换位置:j--
  > 3 换方向继续进行比较，这次从i开始，选择左边比key大的内容，之后两者交换位置，之后换方向继续比较。
#### 图解
![](assets/quick_sort.gif)
#### 代码实现
```c
#include <stdio.h>
#include <stdlib.h>
#include <mach/task.h>

void print_arr(int arr[],int len)
{
    for(int i=0;i<len;i++)
    {
        printf("%4d",arr[i]);
    }
    printf("\n");
}
void swap_arr(int arr[],int var1, int var2)
{
    int temp=arr[var1];
    arr[var1]=arr[var2];
    arr[var2]=temp;
    return;
}

void quick_sort(int arr[],int begin,int last)
{
    int i=begin,j=last,mid=begin;
    while(i<j) {
        while (i < j) //到达最后的递归没有？
        {
            while( arr[mid] < arr[j] && i < j)
            {
                j--;
            }
            if (i < j) {
                swap_arr(arr, mid,j);
                mid = j;
            } else break;
            while (arr[mid] > arr[i] && i < j)
            {
                i++;
            }
            if (i <j) {
                swap_arr(arr, mid,i);
                mid = i;
            } else break;
        }
    }
    if(begin>=last)
    {
        return ;
    }
    print_arr(arr,14);
    quick_sort(arr,begin,mid-1);
    quick_sort(arr,mid+1,last);
    return;
}

int main()
{
    int arr[]={14,25,78,2,45,69,54,89,94,32,43,16,58,7};
    int len= sizeof(arr)/ sizeof(int);
    //print_arr(arr,len);
    quick_sort(arr,0,len-1);
    print_arr(arr,len);
    return 1;
}
```
