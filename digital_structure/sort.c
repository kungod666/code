#include <stdio.h>
#include <stdlib.h>

//插入排序
void insertSort(int* arr,int size){
    int key;
    for(int i = 1;i < size;i++){//0号不用考虑抓牌
        key = arr[i];
        int j = i -1;
        while(j >=0 && arr[j]>key){
            arr[j+1] = arr[j];//后移
            j--;
        }
        arr[j+1] = key;
    }
}
//最好o(n),平均o(n^2),常用于小数据处理

//折半插入排序
void binary_insertSort(int* arr,int size){
    int key;
    for(int i = 1;i < size;i++){//0号不用考虑抓牌
        key = arr[i];
        int left = 0;
        int right = i-1;
        int mid;
        //加入了二分查找
        //(因为插入排序中左侧i-1部分为已排序)
        while(left <= right){
            mid = left + (right-left)/2;
            if(arr[mid] > key) right = mid-1;
            else if(arr[mid] < key) left = mid+1;
            else if(arr[mid] == key){
                left = mid+1;
                break;
            }
        }
        for(int j = left;j <= i-1;j++){
            arr[j+1] = arr[j];
        }
        arr[left] = key;
    }
}
