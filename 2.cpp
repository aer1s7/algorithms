#include <iostream>
#include <algorithm>
#include <vector>

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

vector<string> findPrefixes(const string& word){
    vector<string> prefixes;
    string curr = "";

    for (int i = 0; i < word.length() - 1; i++){
        curr += word[i];
        if (search(curr)){
            prefixes.push_back(curr);
        }
    }
    return prefixes;
}

int main(){
    setlocale(LC_ALL, "ru_RU.UTF-8");
    vector<string> words = {"a", "ab", "abc", "abcd", "abcdef", "bcd"};
    for (string word : words){
        insert(word);
    }
    cout << "Изначальное trie дерево: " << endl;
    printTrieWords(root, "");

    string maxWord;
    vector<string> maxPrefixes;

    for (string word : words){
        vector<string> prefixes = findPrefixes(word);
        if (prefixes.size() > maxPrefixes.size()){
            maxPrefixes = prefixes;
            maxWord = word;
        }
    }

    cout << "Слово с наибольшим количеством префиксов: " << maxWord << " (" << maxPrefixes.size() << ")" << endl;
    cout << "Префиксы: ";
    for (string pref : maxPrefixes){
        cout << pref << " ";
    }
}