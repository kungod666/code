#include <stdlib.h>
#include <stdio.h>
/*平均查找长度:
指在一种查找方法下，查找一个元素所需要比较的关键字的平均次数，
是衡量查找算法效率的一个重要指标。它通常分为两种情况讨论
：查找成功和失败*/

//折半查找(二分查找)-->要求必须有序
int binary_Search(int* arr,int size,int num){
    int l = 0;
    int r = size;
    int mid;
    while(l <= r){
        mid = l + (r-l)/2;
        if(arr[mid] > num){
            r = mid-1;
        }
        else if(arr[mid] < num){
            l = mid+1;
        }
        else if(arr[mid] == num){
            return mid;
        }
    }
    return -1;
}
int main(){
    int arr[] ={1,2,3,4,5,6,7};
    //线性表查找-顺序查找

    printf("%d",binary_Search(arr, 7, 5));
}
