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

void heapPush(vector<int>& data, int value){
    data.push_back(value);
    siftUp(data, data.size() - 1);
}

int heapPop(vector<int>& data){
    int result = data[0];
    data[0] = data.back();
    data.pop_back();
    if (!data.empty()){
        siftDown(data, 0);
    }
    return result;
}

void buildHeap(vector<int>& data){
    int n = data.size();
    for (int i = n / 2 - 1; i >= 0; --i){
        siftDown(data, i);
    }
}

int main(){
    setlocale(LC_ALL, "ru_RU.UTF-8");
    vector<int> ropes = {13,8,3,10,5,12,15};
    buildHeap(ropes);
    cout << "Исходные длины канатов: ";
    printHeap(ropes);
    cout << "Порядок связывания канатов: " << endl;
    int total = 0;
    while (ropes.size() > 1){
        int rope1 = heapPop(ropes);
        int rope2 = heapPop(ropes);
        int step = rope1 + rope2;
        total += step;
        cout << rope1 << " + " << rope2 << " = " << step << " (Сумм. " << total << ")" << endl;
    }
    cout << "Суммарные затраты: " << total;
}