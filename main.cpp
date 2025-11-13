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

int main(){


return 0;
}
