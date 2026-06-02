#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Task{
    string name;
    int priority;
};

class Todolist{
    private:
        vector<Task> heap;
    public:
        void siftUp(int index){
            while (index > 0){
                int parent = (index - 1) / 2;
                if (heap[index].priority <= heap[parent].priority){
                    break;
                }
                swap(heap[index], heap[parent]);
                index = parent;
            }
        }

        void siftDown(int index){
            int size = heap.size();
            while (true){
                int left = 2*index + 1;
                int right = 2*index + 2;
                int largest = index;
                if (left < size && heap[left].priority > heap[largest].priority){
                    largest = left;
                }
                if (right < size && heap[right].priority > heap[largest].priority){
                    largest = right;
                }
                if (largest == index){
                    break;
                }
                swap(heap[largest], heap[index]);
                index = largest;
            }
        }

        void print(){
            for (Task t : heap){
                cout << "(Задача: " << t.name << ", приоритет: " << t.priority << ") ";
            }
            cout << endl;
        }

        void addTask(string name, int priority){
            heap.push_back({name, priority});
            siftUp(heap.size() - 1);
            cout << "Добавлена задача: " << name << " (приоритет " << priority << ")" << endl;
        }

        bool isEmpty(){
            if (heap.empty()) return true;
            return false; 
        }

        Task doTask(){
            if (heap.empty()){
                cout << "Список пуст." << endl;
                return {"", -1};
            }
            Task mx = heap[0];
            heap[0] = heap.back();
            heap.pop_back();
            if (!heap.empty()){
                siftDown(0);
            }

            return mx;
        }

        void editTask(string name, int newPriority){
            for (int i = 0; i < heap.size(); ++i){
                if (heap[i].name == name){
                    int oldPriority = heap[i].priority;
                    heap[i].priority = newPriority;
                    cout << "Приоритет " << heap[i].name << " изменен на " << heap[i].priority << endl;
                    if (oldPriority < newPriority){
                        siftUp(i);
                    }
                    else {
                        siftDown(i);
                    }
                    return;
                }
            }
            cout << "Задача не найдена." << endl;
            return;
        }
};

int main(){
    setlocale(LC_ALL, "ru_RU.UTF-8");
    Todolist list;
    list.addTask("walk", 1);
    list.addTask("work", 3);
    list.addTask("shopping", 2);
    list.addTask("study", 4);
    list.print();
    list.editTask("work", 5);
    list.addTask("gym", 3);
    cout << "Список после изменений: " << endl;
    list.print();
    cout << endl << "Выполнение задач по приоритету: " << endl;
    while (!list.isEmpty()){
        Task curr = list.doTask();
        cout << "Выполнена задача: " << curr.name << " (приоритет " << curr.priority << ")" << endl;
    }
}