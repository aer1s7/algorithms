#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class BinaryHeap{
    private: 
        vector<int> data;

        void siftUp(int index){
            while (index > 0){
                int parent = (index - 1) / 2;
                if (data[index] <= data[parent]){
                    break;
                }
                swap(data[index], data[parent]);
                index = parent;
            }
        }

        void siftDown(int index){
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

        void buildHeap(){
            int size = data.size();
            for (int i = size/2-1; i >= 0; --i){
                siftDown(i);
            }
        }
    public:
        BinaryHeap() : data({}){};
        BinaryHeap(vector<int> heap){
            data = heap;
            buildHeap();
        }

        int get_max(){
            if (data.empty()){
                cout << "Куча пуста." << endl;
                return -1;
            }
            return data[0];
        }

        int extract_max(){
            if (data.empty()){
                cout << "Куча пуста." << endl;
                return -1;
            }
            int mx = data[0];
            data[0] = data.back();
            data.pop_back();
            if (!data.empty()){
                siftDown(0);
            }

            return mx;
        }

        bool empty(){
            if (data.empty()){
                return true;
            }
            return false;
        }

        void insert(int value){
            data.push_back(value);
            siftUp(data.size()-1);
        }

        void print(){
            for (int val : data){
                cout << val << " ";
            }
            cout << endl;
        }
};

int main(){
    setlocale(LC_ALL, "ru_RU.UTF-8");
    vector<int> priorities = {15,12,7,5,20,9,3};
    BinaryHeap heap(priorities);
    cout << "Исходные приоритеты: ";
    heap.print();
    cout << "Максимальный приоритет: " << heap.get_max() << endl;
    cout << "Извлечение максимального: " << heap.extract_max() << endl;
    cout << "Куча после извлечения: ";
    heap.print();
    cout << "Добавление приоритета 18: ";
    heap.insert(18);
    heap.print();
    cout << "Проверка заданий по приоритету: ";
    while (!heap.empty()){
        cout << heap.extract_max() << " ";
    }
}