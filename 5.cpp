#include <iostream>
#include <queue>

using namespace std;

struct Node{
    int value;
    Node* left;
    Node* right;
    Node(int x) : value(x), left(nullptr), right(nullptr) {}
};

// Проверка на полноту (если встретили пустой узел, то все последующие тоже пустые).
bool isComplete(Node* root){ 
    if (!root) return true;
    queue<Node*> q;
    q.push(root);
    bool foundNull = false;

    while (!q.empty()){
        Node* curr = q.front();
        q.pop();

        if (!curr){
            foundNull = true;
        } else {
            if (foundNull) return false;
            q.push(curr->left);
            q.push(curr->right);
        }
    }
    return true;
}
//Проверка на свойства max-кучи
bool isMaxHeap(Node* root){
    if (!root) return true;
    if (root->left && root->value < root->left->value) return false;
    if (root->right && root->value < root->right->value) return false;
    return isMaxHeap(root->left) && isMaxHeap(root->right);
}
//Проверка на свойства min-кучи
bool isMinHeap(Node* root){
    if (!root) return true;
    if (root->left && root->value > root->left->value) return false;
    if (root->right && root->value > root->right->value) return false;
    return isMinHeap(root->left) && isMinHeap(root->right);
}
//Общая проверка полноты и свойств кучи
bool isTreeHeap(Node* root){
    if (!root) return true;
    if (!isComplete(root)) return false;
    return isMaxHeap(root) || isMinHeap(root);
}

int main(){
    setlocale(LC_ALL, "ru_RU.UTF-8");
    Node* root1 = new Node(10); // Max-heap дерево
    root1->left = new Node(7);
    root1->right = new Node(5);
    root1->left->left = new Node(1);
    root1->left->right = new Node(2);
    root1->right->left = new Node(3);
    cout << "Тест 1 (Max-heap): " << isTreeHeap(root1) << endl;
    Node* root2 = new Node(1); // min-heap дерево
    root2->left = new Node(3);
    root2->right = new Node(2);
    root2->left->left = new Node(5);
    root2->left->right = new Node(4);
    root2->right->left = new Node(6);
    cout << "Тест 2 (Min-heap): " << isTreeHeap(root2) << endl;
    Node* root3 = new Node(10); // min-heap дерево
    root3->left = new Node(15);
    root3->right = new Node(5);
    root3->left->left = new Node(1);
    root3->left->right = new Node(2);
    root3->right->left = new Node(3);
    cout << "Тест 3 (Не куча): " << isTreeHeap(root3) << endl;
}