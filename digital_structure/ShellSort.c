#include <stdio.h>
#include <stdlib.h>
//希尔排序:o(n^(1+k))(0 < k < 1)--->不追求最优(稳定性不好)但在中等数据规模实现简单高效
void shellSort(int* data,int len){
    int temp;
    //初始化步长为数组长度的一半
    int step = len/2;
    while(step >= 1){
        //对每个分组执行插入排序
        for(int i = step;i < len;i++){
            if(data[i] < data[i-step]){
                temp = data[i];
                int j = i - step;

                while(j >= 0 && temp < data[j]){
                    data[j+step] = data[j];
                    j -=step;
                }
                data[j+step] = temp;
            }
        }
        step /=2;
    }
}