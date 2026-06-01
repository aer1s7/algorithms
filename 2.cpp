#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void siftUp(vector<int>& data, int index){
    while (index > 0){
        int parent = (index - 1) / 2;
        if (data[index] >= data[parent]){
            break;
        }
        swap(data[index], data[parent]);
        index = parent;
    }
}

void siftDown(vector<int>& data, int index){
    int size = data.size();
    while (true){
        int left = 2*index + 1;
        int right = 2*index + 2;
        int smallest = index;
        if (left < size && data[left] < data[smallest]){
            smallest = left;
        }
        if (right < size && data[right] < data[smallest]){
            smallest = right;
        }
        if (smallest == index){
            break;
        }
        swap(data[smallest], data[index]);
        index = smallest;
    }
}

void printHeap(vector<int> data){
    for (int val : data){
        cout << val << " ";
    }
    cout << endl;
}

void heapPush(vector<int>& data, int time){
    data.push_back(time);
    siftUp(data, data.size() - 1);
}

void heapPop(vector<int>& data, int time){
    data[0] = data.back();
    data.pop_back();
    if (!data.empty()){
        siftDown(data, 0);
    }
}

int main(){
    setlocale(LC_ALL, "ru_RU.UTF-8");
    vector<int> heap;
    heapPush(heap, 14);
    heapPush(heap, 6);
    heapPush(heap, 9);
    heapPush(heap, 20);
    heapPush(heap, 17);
    heapPush(heap, 5);
    cout << "Массив работ для проверки: ";
    printHeap(heap);
    cout << "Порядок проверки работ (по времени сдачи): ";
    while (!heap.empty()){
        cout << heap[0] << " ";
        heapPop(heap, heap[0]);
    }
}