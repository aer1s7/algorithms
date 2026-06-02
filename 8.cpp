#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>

using namespace std;
using namespace chrono;

struct Stats{
    long long comparsions = 0;
    long long swaps = 0;
};

void siftDown(vector<int>& arr, int index, int size, Stats& stats){
    while (true){
        int left = 2*index+1;
        int right = 2*index+2;
        int largest = index;

        if (left < size){
            stats.comparsions++;
            if (arr[left] > arr[largest]){
                largest = left;
            }
        }
        if (right < size){
            stats.comparsions++;
            if (arr[right] > arr[largest]){
                largest = right;
            }
        }
        if (largest == index){
            break;
        }
        swap(arr[index], arr[largest]);
        stats.swaps++;
        index = largest;
    }
}

void heapSort(vector<int>& arr, Stats& stats){
    int n = arr.size();
    for (int i = n/2-1; i>=0; --i){
        siftDown(arr, i, n, stats);
    }

    for (int i = n - 1; i > 0; --i){
        swap(arr[0], arr[i]);
        stats.swaps++;
        siftDown(arr, 0, i, stats);
    }
}

void bubbleSort(vector<int>& arr, Stats& stats){
    int n = arr.size();
    for (int i = 0;i < n-1; ++i){
        for (int j = 0; j < n-i-1; ++j){
            stats.comparsions++;
            if (arr[j] > arr[j+1]){
                swap(arr[j], arr[j+1]);
                stats.swaps++;
            }
        }
    }
}

void insertionSort(vector<int>& arr, Stats& stats){
    int n = arr.size();
    for (int i = 1; i < n; i++){
        int key = arr[i];
        int j = i-1;
        while (j >= 0){
            stats.comparsions++;
            if (arr[j] > key){
                arr[j+1] = arr[j];
                stats.swaps++;
                j--;
            }
            else {
                break;
            }
        }
        arr[j+1] = key;
    }
}

void selectionSort(vector<int>& arr, Stats& stats){
    int n = arr.size();
    for (int i = 0; i < n-1; ++i){
        int minindex = i;
        for (int j = i+1;j<n;++j){
            stats.comparsions++;
            if (arr[j] < arr[minindex]){
                minindex = j;
            }
        }
        if (minindex != i){
            swap(arr[i], arr[minindex]);
            stats.swaps++;
        }
    }
}

int partition(vector<int>& arr, int low, int high, Stats& stats){
    int x = arr[high];
    int i = low-1;
    for (int j = low; j <high; ++j){
        stats.comparsions++;
        if (arr[j] <= x){
            i++;
            swap(arr[i], arr[j]);
            stats.swaps++;
        }
    }
    swap(arr[i+1], arr[high]);
    stats.swaps++;
    return i+1;
}

void quickSort(vector<int>& arr, int low, int high, Stats& stats){
    if (low < high){
        int xindex = partition(arr, low, high, stats);
        quickSort(arr, low, xindex-1, stats);
        quickSort(arr, xindex+1, high, stats);
    }
}

void runSort(string sortName, vector<int> arr, void (*sortfunc)(vector<int>&, Stats&)){
    Stats stats;
    auto start = high_resolution_clock::now();
    sortfunc(arr, stats);
    auto end = high_resolution_clock::now();
    auto time = duration_cast<milliseconds>(end-start).count();
    cout << sortName << endl;
    cout << "Время: " << time << "мс" << endl;
    cout << "Сравнения: " << stats.comparsions << endl;
    cout << "Перестановки: " << stats.swaps << endl;
    cout << endl;
}

void runQuickSort(vector<int> arr){
    Stats stats;
    auto start = high_resolution_clock::now();
    quickSort(arr, 0, arr.size()-1, stats);
    auto end = high_resolution_clock::now();
    auto time = duration_cast<milliseconds>(end-start).count();
    cout << "Быстрая сортировка" << endl;
    cout << "Время: " << time << "мс" << endl;
    cout << "Сравнения: " << stats.comparsions << endl;
    cout << "Перестановки: " << stats.swaps << endl;
    cout << endl;
}

vector<int> generateRandom(int n){
    vector<int> arr(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100000);
    for (int i = 0; i < n; i++){
        arr[i] = dis(gen);
    }
    return arr;
}

vector<int> generateSorted(int n){
    vector<int> arr(n);
    for (int i = 0; i < n; i++){
        arr[i] = i;
    }
    return arr;
}

vector<int> generateSortedReverse(int n){
    vector<int> arr(n);
    for (int i = 0; i < n; i++){
        arr[i] = n - i;
    }
    return arr;
}

vector<int> generatePartSorted(int n){
    vector<int> arr = generateSorted(n);
    int swaps_count = 0.05*n;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, n-1);
    for (int i = 0;i<swaps_count; i++){
        swap(arr[dis(gen)], arr[dis(gen)]);
    }
    return arr;
}

void testArray(string testName, vector<int> arr){
    cout << "==========================" << endl;
    cout << testName << endl;
    cout << "Размер массива: " << arr.size() << endl;
    cout << "==========================" << endl;
    runSort("Пузырьковая сортировка", arr, bubbleSort);
    runSort("Сортировка вставками", arr, insertionSort);
    runSort("Сортировка выбором", arr, selectionSort);
    runSort("Пирамидальная сортировка", arr, heapSort);
    runQuickSort(arr);
}

int main(){
    setlocale(LC_ALL, "ru_RU.UTF-8");
    vector<int> smallPartSorted = generatePartSorted(500);
    vector<int> smallReverseSorted = generateSortedReverse(500);
    vector<int> smallSorted = generateSorted(500);
    vector<int> smallRandom = generateRandom(500);
    vector<int> bigRandom = generateRandom(10000);
    testArray("Небольшой частично отсортированный массив", smallPartSorted);
    testArray("Небольшой массив, отсортированный по убыванию", smallReverseSorted);
    testArray("Небольшой массив, отсортированный по возрастанию", smallSorted);
    testArray("Небольшой случайный массив", smallRandom);
    testArray("Большой случайный массив", bigRandom);
}