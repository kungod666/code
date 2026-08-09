#include <stdio.h>
#include <stdlib.h>
/*选择基准元素，将序列划分为两个子序列
所有比基准元素小的放左边，比基准元素大的
放右边，而后递归对左右序列快排即可*/
//O(n^2) 不稳定
//个人风格(类似挖矿法)
void quickSort(int* data,int low,int high){
    if(low >= high){
        return;
    }
    int pivot = data[low];
    int tp_l = low;
    int tp_h = high;
    while(low < high){
        while(data[high] >= pivot&& low < high){
            high--;
        }
        while(data[low] <= pivot&& low < high){
            low++;
        }
        if(low < high){
            int temp = data[low];
            data[low] = data[high];
            data[high] = temp;
        }
        /*标准挖矿法
        while(low<high && data[low] <= pivot){
        high--
        }
        data[low] = data[high];
        while(low < high && data[low] <= pivot){
        low++;
        }
        data[high] = data[low];*/
    }
    data[tp_l] = data[low];
    data[low] = pivot;
    quickSort(data,tp_l, low-1);
    quickSort(data,low+1,tp_h);
}
//涉及到边界检查，易错


//Lomuto分区
void Lomu_quickSort(int* data,int low,int high){
    if(low >= high) return;

    int pivot = data[high];
    int i = low-1;
    for(int j = low;j < high;j++){
        if(data[j] <= pivot){
            i++;//此处特点表明i+1处数据一定大于pivot
            int temp = data[i];
            data[i] = data[j];
            data[j] = temp;
        }
    }
    //通过i的后动，避免了边界检查
    int temp = data[i+1];
    data[i+1] = data[high];
    data[high] = temp;

    //现在i+1为pivot
    Lomu_quickSort(data, low, i);
    Lomu_quickSort(data, i+2, high);
}