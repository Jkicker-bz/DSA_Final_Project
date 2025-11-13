#include <iostream>
#include <string>
using namespace std;

// Each Trie Node can store up to 26 letters (a-x)
Struct TrieNode {
     TrieNode* children[26];
     bool isEndOfWord;
};

TrieNode* getNode(){
     TrieNode* node = new TrieNode;
     node->isEndOfWord = false;
     for (int i = 0; i < 26; i++)
	node->children[i] = nullptr;
     return node;
}

void insert(TrieNode* root, string word) {
    TrieNode* curr = root;
    for (char c : word) {
        int index = c - 'a';
        if (curr->children[index] == nullptr)
            curr->children[index] = createNode();
        curr = curr->children[index];
    }
    curr->isEndOfWord = true;
}

bool search(TrieNode* root, string word) {
    TrieNode* curr = root;
    for (char c : word) {
        int index = c - 'a';
        if (curr->children[index] == nullptr)
            return false;
        curr = curr->children[index];
    }
    return curr->isEndOfWord;
}

void removeWord(TrieNode* root, string word) {
    TrieNode* curr = root;
    for (char c : word) {
        int index = c - 'a';
        if (curr->children[index] == nullptr)
            return; // word not found
        curr = curr->children[index];
    }
    curr->isEndOfWord = false; // unmark as a word
}
int main(){


return 0;
}9
