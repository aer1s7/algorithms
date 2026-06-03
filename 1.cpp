#include <iostream>
#include <algorithm>

using namespace std;

struct TrieNode{
    TrieNode* children[26];
    bool isEndOfWord;

    TrieNode(){
        isEndOfWord = false;
        for (int i = 0; i < 26; i++){
            children[i] = nullptr;
        }
    }
};

TrieNode* root = new TrieNode();

void insert(const string& word){
    TrieNode* node = root;
    for (char ch : word){
        int index = ch - 'a';
        if (node->children[index] == nullptr){
            node->children[index] = new TrieNode();
        }
        node = node->children[index];
    }
    node->isEndOfWord = true;
}

bool search(const string& word){
    TrieNode* node = root;
    for (char ch : word){
        int index = ch - 'a';
        if (node->children[index] == nullptr){
            return false;
        }
        node = node->children[index];
    }
    return node->isEndOfWord;
}

bool isEmpty(TrieNode* node){
    for (int i = 0; i < 26; i++){
        if (node->children[i] != nullptr){
            return false;
        }
    }
    return true;
}

bool removeWord(TrieNode* node, const string& word, int depth){
    if (node == nullptr){
        return false;
    }
    if (depth == word.length()){
        if (!node->isEndOfWord){
            return false;
        }
        node->isEndOfWord = false;

        return isEmpty(node);
    }

    int index = word[depth] - 'a';
    bool deleteChild = removeWord(node->children[index], word, depth+1);
    if (deleteChild){
        delete node->children[index];
        node->children[index] = nullptr;
    }

    return !node->isEndOfWord && isEmpty(node);
}

void remove(const string& word){
    if (!search(word)){
        cout << "Слово " << word << " не найдено." << endl;
        return;
    }
    removeWord(root, word, 0);
    cout << "Слово " << word << " успешно удалено." << endl;
}

void printTrieWords(TrieNode* node, string currentWord){
    if (node == nullptr){
        return;
    }    
    if (node->isEndOfWord){
        cout << currentWord << endl;
    }
    for (int i = 0; i < 26; i++){
        if (node->children[i] != nullptr){
            char ch = 'a' + i;
            printTrieWords(node->children[i], currentWord+ch);
        }
    }
}

int main(){
    setlocale(LC_ALL, "ru_RU.UTF-8");
    insert("hello");
    insert("world");
    insert("heaven");
    insert("heavy");
    cout << "Изначальное trie дерево: " << endl;
    printTrieWords(root, "");
    cout << "Поиск слова до удаления: " << endl;
    string word = "heavy";
    if (search(word)){
        cout << "Слово " << word << " найдено." << endl; 
    } else {
        cout << "Слово " << word << " не найдено." << endl;
    }
    remove(word);
    cout << "Поиск слова после удаления: " << endl;
    if (search(word)){
        cout << "Слово " << word << " найдено." << endl; 
    } else {
        cout << "Слово " << word << " не найдено." << endl;
    }
}