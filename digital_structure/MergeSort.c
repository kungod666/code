#include <stdio.h>
#include <stdlib.h>
/*time:O(nlogn);space:O(n)
stable sort*/
void merge(int* data,int left,int mid,int right){
    int temp[100];//临时数组，用于存放合并结果
    int i = left;//左半部分
    int j = mid+1;//右半部分
    int k = 0;
    while(i  <= mid && j <= right){
        if(data[i] <= data[j]){
            temp[k++] = data[i++];
        }
        else{
            temp[k++] = data[j++];
        }
    }
    while(i <= mid){//左半剩余部分拷贝(如果有)
        temp[k++] = data[i++];
    }
    while(j <= right){
        temp[k++] = data[j++];
    }
    for(int t = 0;t < k;t++){
        data[left+t] = temp[t];//拷贝回去
    }
}

void mergeSort(int* data,int left,int right){
    if(left < right) //至少两个元素才需要排序
    {
        int mid = (left+right)/2;

        //对左半部分排序
        mergeSort(data, left, mid);
        //对右半部分排序
        mergeSort(data, mid+1, right);

        merge(data,left,mid,right);
    }
}