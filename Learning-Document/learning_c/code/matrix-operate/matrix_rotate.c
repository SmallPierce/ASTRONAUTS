/* 矩阵顺时针旋转90°
有一个NxN整数矩阵，请编写一个算法，将矩阵顺时针旋转90度。
给定一个NxN的矩阵，和矩阵的阶数N,请返回旋转后的NxN矩阵,保证N小于等于300。
eg:
    1 2 3    7 4 1
    4 5 6    8 5 2
    7 8 9    9 6 3
*/

/*
  算法描述，将矩阵的每一个元素，与旋转后的元素对比，发现下面规律
  arr[i][j] 要被arr[3-j][i]的元素代替
  每个角上的元素按照上述的方法要替换一次，每次可以换4个位置的内容
  所以，我们只需要把左上角的内容换了即可
*/
#include <stdio.h>

void Maxtix_rotate1_(int (*arr)[4], int N) {
  int i, j, temp;
  int i1, j1;
  //对矩阵进行分块，分成四块，每一块采用相关的回旋手法即可。
  for (i = 0; i < (int)N / 2; i++) {

    for (j = 0; j < (int)N / 2; j++) {
      i1 = i;
      j1 = j;
      temp = arr[i1][j1]; //保存目前的值

      //第四象限的数据每个要与四块进行迭代，先进行三次变换
      for (int k = 0; k < 3; k++) {
        arr[i1][j1] = arr[3 - j1][i1];
        int var1 = i1;
        int var2 = j1;
        j1 = var1;
        i1 = 3 - var2;
      }
      //将temp里面的数据放在最后一个位置上
      arr[i1][j1] = temp;
    }
  }
  return;
}

int main() {
  printf("Hello, World!\n");
  int arr[4][4] = {
      {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
  Maxtix_rotate1_(arr, 4);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      printf("%4d", arr[i][j]);
    }
    printf("\n");
  }
  return 0;
}
