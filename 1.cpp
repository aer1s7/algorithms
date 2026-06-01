#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

void siftDown(vector<int>& data, int index){
    int size = data.size();
    while (true){
        int left = 2*index + 1;
        int right = 2*index + 2;
        int largest = index;
        if (left < size && data[left] > data[largest]){
            largest = left;
        }
        if (right < size && data[right] > data[largest]){
            largest = right;
        }
        if (largest == index){
            break;
        }
        swap(data[largest], data[index]);
        index = largest;
    }
}

void buildHeap(vector<int>& data){
    int n = data.size();
    for (int i = n / 2 - 1; i >= 0; --i){
        siftDown(data, i);
    }
}

void printHeap(vector<int> data){
    for (int val : data){
        cout << val << " ";
    }
    cout << endl;
}

int main(){
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int n = 0;
    cout << "Введите размер массива: ";
    cin >> n;
    vector<int> heap(n);
    cout << "Введите элементы массива: ";
    for (int i = 0; i < n;i++){
        cin >> heap[i];
    }
    buildHeap(heap);
    printHeap(heap);
}