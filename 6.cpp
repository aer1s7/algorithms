#include <iostream>
#include <algorithm>

using namespace std;

struct Node{
    int data;
    int priority;
    Node* next;
    Node(int data, int priority){
        this->data = data;
        this->priority = priority;
        next = nullptr;
    }
};

class PriorityQueue{
    private:
        Node* head;

    public:
        PriorityQueue(){
            head = nullptr;
        }

        void insert(int data, int priority){
            Node* newNode = new Node(data, priority);
            if (head == nullptr || priority < head->priority){
                newNode->next = head;
                head = newNode;
                return;
            }
            Node* curr = head;
            while (curr->next != nullptr && curr->next->priority <= priority){
                curr = curr->next;
            }
            newNode->next = curr->next;
            curr->next = newNode;
        }

        int extractMinimum(){
            if (head == nullptr){
                cout << "Очередь пуста" << endl;
                return -1;
            }
            Node* temp = head;
            int result = head->data;
            head = head->next;
            delete temp;
            return result;
        }

        bool isEmpty(){
            return head == nullptr;
        }

        void print(){
            Node* curr = head;

            while (curr != nullptr){
                cout << "(Ключ: " << curr->data << ", приоритет: " << curr->priority << ") ";
                curr = curr->next;
            }
            cout << endl;
        }
};

int main(){
    setlocale(LC_ALL, "ru_RU.UTF-8");
    PriorityQueue q;
    q.insert(60, 2);
    q.insert(50, 4);
    q.insert(10, 1);
    q.insert(30, 3);
    cout << "Очередь с приоритетом: " << endl;
    q.print();
    cout << "Извлечение по приоритету: " << endl;
    while (!q.isEmpty()){
        cout << "Извлечено " << q.extractMinimum() << endl;
    }
}