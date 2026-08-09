#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
//O(nlogn)
//实际上，一个大顶堆其实就是priority_deque
int data[] = {19,2,21,12,34,23};
void adjust(int* arr,int root,int len){
    int temp = arr[root];
    int child = 2*root;
    while(child <= len){
        if(child+1 <=len && arr[child] < arr[child+1]){
            child++;
        }
        if(temp > arr[child]){//不断下沉时temp值也下降到这一层
            break;
        }
        arr[child/2] = arr[child];
        child = child*2;//逐层深入，是将temp送入正确层数关键
        //而大顶堆要求的"顶部大于下层所有数字是child深入的充分条件
    }
    arr[child/2] = temp;
}
void swap(int* arr,int i,int j){
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}
//建堆
int* bulidHeap(int* data,int len){
    int* arr = (int*)malloc((len+1)*sizeof(int));
    arr[0] = -1;
    for(int i = 0;i < len;i++){
        arr[i+1] = data[i];
    }
    for(int i = (len/2);i > 0;i--){
        //维持全局有序实际上依靠 i = len/2, i--，即自大值向小值移动维护
        adjust(arr,i,len);
    }
    return arr;
}
//堆插入
int* insertHeap(int* arr,int len,int val){
    int* new_arr = (int*)realloc(arr,(len+2)*sizeof(int));
    new_arr[len+1] = val;
    int k = len+1;
    while(k > 0 && new_arr[k/2] < new_arr[k]){
        swap(new_arr,k/2,k);
        k /= 2;
    }
    return new_arr;
}
//堆删除(只删除堆顶，否则O(n)无法体现priority_qeque优势)
int* delete_top(int* arr,int len,int val){
    swap(arr,1,len);
    int* new_arr = (int*)realloc(arr, (len-1)*sizeof(int));
    adjust(new_arr, 1, len-1);
    return new_arr;
}
//堆排序
int* heapSort(int* data,int len){
    int* arr = bulidHeap(data, len);
    for(int i = len;i > 0;i--){
        swap(arr,1,i);
        adjust(arr,1,i-1);
        //建立在2-->(i-1)大顶堆基础没破坏基础
    }
    return arr;
}

int main(){
    int len = sizeof(data)/sizeof(data[0]);
    int* arr = heapSort(data, len);
    for(int i = 1;i <= len;i++){
        printf("%d ",arr[i]);
    }
}